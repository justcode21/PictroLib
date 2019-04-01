## PictroLib
PictroLib is a classic crossplatform image processing library developed to be integrated as a backend for an image editing application 
that I plan to make. It can perform the basic operations on both Black-White and coloured images and can also be extended to add more functionalitites depending on the need of the application.

Currently it supports only .BMP files and has the appropriate mechanisms to read, parse and manipulate the image data. Some features include - 

### Rotation/Mirror
The current implementation support the followings directions.

```
LEFT
RIGHT
UPSIDEDOWN
MIRROR
```
<table width = "100%">
<td><img src = "Images/cameraman.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/cameraman_left_rotated.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/cameraman_mirror_rotated.bmp" width = 250 height = 250></td>
</table>

### Brightness
The current implementation support the followings options

```
increaseBrightess(factor)
decreaseBrightness(factor)
```
<table width = "100%">
<td><img src = "Images/Land.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/Land_increased_brightness.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/Land_decreased_brightness.bmp" width = 250 height = 250></td>
</table>

### Contrast
The contrast is created by equalizing the image histogram.

```
Add Images here
```
<table width = "100%">
<td><img src = "Images/girlface.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/girlface_contrast.bmp" width = 250 height = 250></td>
</table>

### Negetive
The blur is calculated by simply inverting the pixel values at each pixel.
<table width = "100%">
<td><img src = "Images/cameraman.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/cameraman_negetive.bmp" width = 250 height = 250></td>
</table>

### Blur
The blur is calculated by convolution of the image with the KERNAL_FILTER

```cpp
static const float KERNAL_FILTER[3][3] =  {
    {1.0/9.0, 1.0/9.0, 1.0/9.0},
    {1.0/9.0, 1.0/9.0, 1.0/9.0},
    {1.0/9.0, 1.0/9.0, 1.0/9.0}
};
```
<table width = "100%">
<td><img src = "Images/baboon.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/baboon_blur.bmp" width = 250 height = 250></td>
</table>


### Sepia
The values for sepia filter is taken from the internet and in the same way we can add many other classic filters

```cpp
r = (m_imageData[i][0] * 0.393) + (m_imageData[i][1] * 0.769) + (m_imageData[i][2] * 0.189);
g = (m_imageData[i][0] * 0.349) + (m_imageData[i][1] * 0.686) + (m_imageData[i][2] * 0.168);
b = (m_imageData[i][0] * 0.272) + (m_imageData[i][1] * 0.534) + (m_imageData[i][2] * 0.131);
```
<table width = "100%">
<td><img src = "Images/baboon.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/baboon_sepia.bmp" width = 250 height = 250></td>
</table>

### Maximum
The maximum filter assigns each pixel with a value which is the maximum in a given viscinity. For 3, 5, 9 for 
1, 2, 3 level deep neighbours.

```cpp
applyMaxFliter(depth)
```
<table width = "100%">
<td><img src = "Images/Ray.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/Ray_max_3.bmp" width = 250 height = 250></td>
<td><img src = "Images/Ray_max_5.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/Ray_max_9.bmp" width = 250 height = 250></td>
</table>

### Minimum
The minimum filter assigns each pixel with a value which is the maximum in a given viscinity. For 3, 5, 9 for 
1, 2, 3 level deep neighbours.

```cpp
applyMinFilter(depth)
```
<table width = "100%">
<td><img src = "Images/Land.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/Land_min_3.bmp" width = 250 height = 250></td>
<td><img src = "Images/Land_min_5.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/Land_min_9.bmp" width = 250 height = 250></td>
</table>

### Median
The median filter assigns each pixel with a value which is the median in a given viscinity. For 3, 5, 9 for 
1, 2, 3 level deep neighbours.

```cpp
applyMedian(depth)
```
<table width = "100%">
<td><img src = "Images/baboon.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/baboon_median_3.bmp" width = 250 height = 250></td>
<td><img src = "Images/baboon_median_5.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/baboon_median_9.bmp" width = 250 height = 250></td>
</table>

### Convolution Masks/Edge Detection
We use a variety of populare edge dectedtion masks which after convolution with the image data give us some solid edges
in any desired direction.

```cpp
LINE_DETECTOR_HOR_MASK,
LINE_DETECTOR_VER_MASK,
LINE_DETECTOR_LDIA_MASK,
LINE_DETECTOR_RDIA_MASK,

//Prewitt Masks
PREWITT_HOR,
PREWITT_VER,

//Sobel Masks
SOBEL_HOR,
SOBEL_VER,

//Robinson Masks(Compass Operator)
ROBINSON_NORTH,
ROBINSON_NORTHEAST,
ROBINSON_EAST,
ROBINSON_SOUTHEAST,
ROBINSON_SOUTH,
ROBINSON_SOUTHWEST,
ROBINSON_WEST,
ROBINSON_NORTHWEST,

//Kirsch Masks(Compass Operator)
KIRSCH_NORTH,
KIRSCH_NORTHEAST,
KIRSCH_EAST,
KIRSCH_SOUTHEAST,
KIRSCH_SOUTH,
KIRSCH_SOUTHWEST,
KIRSCH_WEST,
KIRSCH_NORTHWEST,

//Laplacian Masks
LAPLACIAN_NEGETIVE,
LAPLACIAN_POSITIVE,

//High Pass FIlter(Sharpner)
IMAGE_SHARPNER
```
<table width = "100%">
<td><img src = "Images/houses.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/houses_horizontal.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/houses_vertical.bmp" width = 250 height = 250></td>
</table>

### Gaussian Noise
Produce Gaussian noise for a given image 

<table width = "100%">
<td><img src = "Images/girlface.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/girlface_noise.bmp" width = 250 height = 250></td>
</table>

### Salt and Pepper Noise
Produce grainy noice with a given intensity. For example in this case we generate two grainy 
noises on a sample image with .1 and .3 intensity.
```
generateNoise(intensity)

```

<table width = "100%">
<td><img src = "Images/girlface.bmp" width = 250 height = 250></td>
<td align = "center"><img src = "Images/girlface_noise_1.bmp" width = 250 height = 250></td>
<td align = "right"><img src = "Images/girlface_noise_3.bmp" width = 250 height = 250></td>
</table>



That is it for the Library, there are a few more operations for which I have not attached the photos but you can play with the 
convolution masks and even add some of your own in the Constants file and attach the results here. :)


