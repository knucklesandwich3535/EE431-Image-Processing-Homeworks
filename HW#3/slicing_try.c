// gcc slicing_try.c -o slicing_try img_pro.c -lm
// ./slicing_try lenna.ppm 1

#include "img_pro.h"

color **cgaussf(color **img, int flag, int NC, int NR, int count)
{
	color **temp_1;
	color **temp_2;
	int i , j , k , padding;
	temp_1 = (color **)alloc_color_img(NC , NR); // to allocate space for corrected pixel values (same size with img)
	temp_2 = (color **)alloc_color_img(NC , NR); // to allocate space for corrected pixel values (same size with img)
	padding = count / 2; // define a padding which prevents segmentation faults
	if(flag == 0)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].r=img[i][j].r; // to process the gaussian filter for red pixels, and not destroy the original img, temp_1 used as a temporary variable
						temp_1[i][j].g=img[i][j].g; // to process the gaussian filter for green pixels, and not destroy the original img, temp_1 used as a temporary variable
						temp_1[i][j].b=img[i][j].b; // to process the gaussian filter for blue pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].r = (temp_1[i][j-1].r + 2 * temp_1[i][j].r + temp_1[i][j+1].r) / 4; // horizontal mask was done to red pixels and stored in temp_2 variable
							temp_2[i][j].g = (temp_1[i][j-1].g + 2 * temp_1[i][j].g + temp_1[i][j+1].g) / 4; // horizontal mask was done to green pixels and stored in temp_2 variable
							temp_2[i][j].b = (temp_1[i][j-1].b + 2 * temp_1[i][j].b + temp_1[i][j+1].b) / 4; // horizontal mask was done to blue pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].r = (temp_2[i-1][j].r + 2 * temp_2[i][j].r + temp_2[i+1][j].r) / 4; // vertical mask was done to red pixels and stored in temp_1 varible
							temp_1[i][j].g = (temp_2[i-1][j].g + 2 * temp_2[i][j].g + temp_2[i+1][j].g) / 4; // vertical mask was done to green pixels and stored in temp_1 varible
							temp_1[i][j].b = (temp_2[i-1][j].b + 2 * temp_2[i][j].b + temp_2[i+1][j].b) / 4; // vertical mask was done to blue pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	else if(flag == 1)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].r=img[i][j].r; // to process the gaussian filter for red pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].r = (temp_1[i][j-1].r + 2 * temp_1[i][j].r + temp_1[i][j+1].r) / 4; // horizontal mask was done to red pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].r = (temp_2[i-1][j].r + 2 * temp_2[i][j].r + temp_2[i+1][j].r) / 4; // vertical mask was done to red pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	else if(flag == 2)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].g=img[i][j].g; // to process the gaussian filter for green pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].g = (temp_1[i][j-1].g + 2 * temp_1[i][j].g + temp_1[i][j+1].g) / 4; // horizontal mask was done to green pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].g = (temp_2[i-1][j].g + 2 * temp_2[i][j].g + temp_2[i+1][j].g) / 4; // vertical mask was done to green pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	else if(flag == 3)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].b=img[i][j].b; // to process the gaussian filter for blue pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].b = (temp_1[i][j-1].b + 2 * temp_1[i][j].b + temp_1[i][j+1].b) / 4; // horizontal mask was done to blue pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].b = (temp_2[i-1][j].b + 2 * temp_2[i][j].b + temp_2[i+1][j].b) / 4; // vertical mask was done to blue pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	free_color_img(temp_2); // since temp_2 is not gonna used, it was freed
	return temp_1; // in the main part, temp_1 variable will be assigned for displaying the processed image, so it was returned
}

int main(int argc , char **argv)
{
int i,j,NR,NC,NR2,NC2,count;
char *ppm_file;
color **img;
color **img_temp;
color **top_left;
color **top_right;
color **bottom_left;
color **bottom_right;


if(argc!=3) 
{
  printf("\nUsage: 627635_hw3 [Image file (*.pgm)] [count]\n");
  printf("\nE.g.   627635_hw3 lenna.ppm 1\n");
  exit(-1); 
}

ppm_file = argv[1]; // 2nd input for which image should be corrected
count = atoi(argv[2]); // 3rd count variable got from user as string, we convert it into integer value to use it. It will be used as a flag to choose if we want to perform Gauss operation or Median operation

img = (color **)ppm_file_to_img(ppm_file , &NC , &NR); // to save uncorrected pixel values
show_pgm_file(ppm_file); // shows uncorrected image

img_temp = (color **)alloc_color_img(NC , NR);		// to allocate space for corrected pixel values (same size with img)
top_left = (color **)alloc_color_img(NC , NR); 		// to allocate space for corrected pixel values (same size with img)
top_right = (color **)alloc_color_img(NC , NR);		// to allocate space for corrected pixel values (same size with img)
bottom_left = (color **)alloc_color_img(NC , NR); 	// to allocate space for corrected pixel values (same size with img)
bottom_right = (color **)alloc_color_img(NC , NR); 	// to allocate space for corrected pixel values (same size with img)
	 

// slicing image into 4 parts and assigning them into their labeled arrays
for(i = 0 ; i < NR ; i++)
{
	for(j = 0 ; j < NC ; j++)
	{
		if(i < NR / 2 && j < NC / 2)
		{
			top_left[i][j] = img[i][j];	// Q1 allocation from img array to the top-left array
		}
		else if(i < NR / 2 && j > NC / 2)
		{
			top_right[i][j] = img[i][j]; 	// Q2 allocation from img array to the top-right array
		}
		else if(i > NR / 2 && j < NC / 2)
		{
			bottom_left[i][j] = img[i][j];	// Q3 allocation from img array to the top-left array
		}
		else if(i > NR / 2 && j > NC / 2)
		{
			bottom_right[i][j] = img[i][j];	// Q4 allocation from img array to the bottom-right array
		}
	}
}

// ----------------------- GAUSSIAN FILTERING MAIN (CALLING THE FUNCTION) PART ----------------------
top_left = cgaussf(img , 0 , NC , NR , count); 		// Filtering part: for top-left, 1 gaussian filter was processed, flag 1 situation occured; which includes RGB pixels.
top_right = cgaussf(img , 1 , NC , NR , count);		// Filtering part: for top-right, 2 gaussian filter was processed, flag 2 situation occured; which includes R pixels.
bottom_left = cgaussf(img , 2 , NC , NR , count);		// Filtering part: for bottom-left, 3 gaussian filter was processed, flag 3 situation occured; which includes G pixels.
bottom_right = cgaussf(img , 3 , NC , NR , count);		// Filtering part: for bottom-right, 4 gaussian filter was processed, flag 4 situation occured; which includes B pixels.

// reconstruct the image by adding up the sliced and filtered pieces according to conditions mentioned below
for(i = 0 ; i < NR ; i++)
{
	for(j = 0 ; j < NC ; j++)
	{
		if(i < NR / 2 && j < NC / 2)
		{
			img_temp[i][j] = top_left[i][j];	// Q1 allocation from top-left array to the img_temp array
		}
		else if(i < NR / 2 && j > NC / 2)
		{
			img_temp[i][j] = top_right[i][j]; 	// Q2 allocation from top_right array to the img_temp array
		}
		else if(i > NR / 2 && j < NC / 2)
		{
			img_temp[i][j] = bottom_left[i][j];	// Q3 allocation from bottom_left array to the img_temp array
		}
		else if(i > NR / 2 && j > NC / 2)
		{
			img_temp[i][j] = bottom_right[i][j];	// Q4 allocation from bottom_right array to the img_temp array
		}
	}
}

// img_temp used to reconstruct the image because, we wanted a non-destructive approach, with this, we saved the original img

// img to pgm conversion and showing part
img_to_ppm_file(img_temp, "gauss_slicing.ppm" , NC , NR); 	// Converting image(matrix) to actual image
show_pgm_file("gauss_slicing.ppm"); 				// Displays the filtered image

// color img free part
free_color_img(top_left);
free_color_img(top_right);
free_color_img(bottom_left);
free_color_img(bottom_right);
free_color_img(img);
free_color_img(img_temp);

return(1);
}
