// gcc hw2.c -o hw2 img_pro.c -lm
// ./hw2 panda.pgm 1
// to choose gauss, write 1 after the .pgm file
// to choose median, write 2 after the .pgm file

#include "img_pro.h"

// ---------------------- GAUSSIAN FILTERING FUNCTION PART ----------------------
unsigned char **gaussf (unsigned char **img , int NC , int NR , int count)
{
	unsigned char **temp_1 , **temp_2; // to not destroy the original img, we need to create new variables to store and process
	int i , j , k , padding;
	temp_1 = alloc_img(NC , NR); // to allocate space for corrected pixel values (same size with img)
	temp_2 = alloc_img(NC , NR); // to allocate space for corrected pixel values (same size with img)
	padding = count / 2; // define a padding which prevents segmentation faults
	
	for(i = padding; i < NR - padding; i++)
	{
		for(j = padding; j < NC - padding; j++)
		{
			for(i = 0 ; i < NR ; i++) 
			{
				for(j = 0 ; j < NC ; j++)
				{
					temp_1[i][j] = img[i][j]; // to process the gaussian filter, and not destroy the original img, temp_1 used as a temporary variable
				}
			}

			for(k = 0 ; k < count ; k++)
			{
				for(i = 0 ; i < NR ; i++)
				{
					for(j = 1 ; j < NC - 1 ; j++)
					{
						temp_2[i][j] = (temp_1[i][j-1] + 2 * temp_1[i][j] + temp_1[i][j+1]) / 4; // horizontal mask was done and stored in temp_2 variable
					}
				}
				for(i = 1 ; i < NR - 1 ; i++)
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j] = (temp_2[i-1][j] + 2 * temp_2[i][j] + temp_2[i+1][j]) / 4; // vertical mask was done and stored in temp_1 varible
					}
				}
			}
		}
	}
	free_img(temp_2); // since temp_2 is not gonna used, it was freed
	return temp_1; // in the main part, temp_1 variable will be assigned for displaying the processed image, so it was returned
}

// ---------------------- MEDIAN FILTERING FUNCTION PART ----------------------
unsigned char **medianf(unsigned char **img, int NC, int NR, int count)
{
	unsigned char **temp_1; // to not destroy the original img, we need to create new variables to store and process
	int i, j, k, l, maxval, maxindex, padding;
	int arr[count * count]; // create an array for filter to hold data
	temp_1= alloc_img(NC,NR); // to allocate space for corrected pixel values (same size with img)
	padding = count / 2; // define a padding which prevents segmentation faults
	
	// for loops and image coordinates includes padding for dynamic size operations
	for(i = padding; i < NR - padding; i++)
	{
		for(j = padding; j < NC - padding; j++)
		{
			
			for(k = 0; k < count; k++)
			{
				for(l = 0; l < count; l++)
				{
					arr[count * k + l] = img[i - padding + k][j - padding + l]; 	// fill the array from pixel and its neighbors			
				}
			} 
			for(k = 0; k < (count * count) / 2 + 1; k++)
			{
				// to the middle term, zero the max values
				maxval = -1; 
				maxindex = 0;
				for(l = 0; l < count * count; l++)
				{
					if(arr[l] > maxval)
					{
						maxval = arr[l];
						maxindex = l;		// find max value
					}
				}
				arr[maxindex] = 0;
			}
			temp_1[i][j] = maxval; 		// resulting pixel value
		}
	}       
	return(temp_1);
}

int main(int argc , char **argv)
{
unsigned char **img , **temp_1 , **top_left , **top_right , **bottom_left , **bottom_right;
char *pgm_file;
int i , j , k , NC , NR , count;

if(argc!=3) 
{
  printf("\nUsage: hw2 [Image file (*.pgm)] [count]\n");
  printf("\nE.g.   hw2 panda.pgm 1\n");
  exit(-1); 
}

pgm_file = argv[1]; // 2nd input for which image should be corrected
count = atoi(argv[2]); // 3rd count variable got from user as string, we convert it into integer value to use it. It will be used as a flag to choose if we want to perform Gauss operation or Median operation

img = pgm_file_to_img(pgm_file , &NC , &NR); // to save uncorrected pixel values
show_pgm_file(pgm_file); // shows uncorrected image

// img allocation part	
temp_1 = alloc_img(2 * NC , 2 * NR);	// to allocate space for corrected pixel values (same size with img)
top_left = alloc_img(NC , NR); 		// to allocate space for corrected pixel values (same size with img)
top_right = alloc_img(NC , NR);		// to allocate space for corrected pixel values (same size with img)
bottom_left = alloc_img(NC , NR); 	// to allocate space for corrected pixel values (same size with img)
bottom_right = alloc_img(NC , NR); 	// to allocate space for corrected pixel values (same size with img)
	 
// ----------------------- GAUSSIAN FILTERING MAIN (CALLING THE FUNCTION) PART ----------------------
if(count == 1)
{	
	top_left = gaussf(img , NC , NR , 1); 			// Filtering part, for top-left, 1 gaussian filter was processed
	top_right = gaussf(img , NC , NR , 2);			// Filtering part, for top-right, 2 gaussian filter was processed
	bottom_left = gaussf(img , NC , NR , 3);		// Filtering part, for bottom-left, 3 gaussian filter was processed
	bottom_right = gaussf(img , NC , NR , 4);		// Filtering part, for bottom-right, 4 gaussian filter was processed
}

// ---------------------- MEDIAN FILTERING MAIN (CALLING THE FUNCTION) PART ----------------------
else if(count == 2)
{
	top_left = medianf(img , NC , NR , 1); 		// Filtering part, for top-left, 1 median filter was processed
	top_right = medianf(img , NC , NR , 2);		// Filtering part, for top-right, 2 median filter was processed
	bottom_left = medianf(img , NC , NR , 3);	// Filtering part, for bottom-left, 3 median filter was processed
	bottom_right = medianf(img , NC , NR , 4);	// Filtering part, for bottom-right, 4 median filter was processed
}

// reconstruct the image by adding up the sliced and filtered pieces according to conditions mentioned below
for(i = 0 ; i < 2 * NR ; i++)
{
	for(j = 0 ; j < 2 *NC ; j++)
	{
		if(i < NR && j < NC)
		{
			temp_1[i][j] = top_left[i][j];			// Q1 allocation from top-left array to the temp_1 array
		}
		else if(i < NR && j > NC)
		{
			temp_1[i][j] = top_right[i][j - NC]; 		// Q2 allocation from top_right array to the temp_1 array
		}
		else if(i > NR && j < NC)
		{
			temp_1[i][j] = bottom_left[i - NR][j];		// Q3 allocation from bottom_left array to the temp_1 array
		}
		else if(i > NR && j > NC)
		{
			temp_1[i][j] = bottom_right[i - NR][j - NC];	// Q4 allocation from bottom_right array to the temp_1 array
		}
	}
}
// temp_1 used to reconstruct the image because, we wanted a non-destructive approach, with this, we saved the original img

// img to pgm conversion and showing part
if(count == 1)
{
	img_to_pgm_file(temp_1 , "gauss.pgm" , NC * 2 , NR * 2); 	// Converting image(matrix) to Grayscale(actual image)
	show_pgm_file("gauss.pgm"); 				// Displays the filtered image
}

if(count == 2)
{
	img_to_pgm_file(temp_1 , "median.pgm" , NC * 2 , NR * 2); 	// Converting image(matrix) to Grayscale(actual image)
	show_pgm_file("median.pgm"); 				// Displays the filtered image
}

// img free part
free_img(top_left);
free_img(top_right);
free_img(bottom_left);
free_img(bottom_right);
free_img(img);
free_img(temp_1);

return(1);
}
