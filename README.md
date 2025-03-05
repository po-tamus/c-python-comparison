# c-python-comparison

# Introduction 
## Goal
- Image parser to convert colored images to black and white? 
- convert an image in RGB format to YCrCb format
- An image stored in RGB format stores each pixel as **3 bytes**, one for red, green and blue. Color ranges are from 0 (black) to 255 (maximum color)
- This should just measure the time difference between the C and Python code execution 
## Key Definitions
- A C **kernel** (distinct from an operating system kernel like the Linux kernel) is a function or library that can be called from a higher level language like Python or Java 
- **YCrCb** format is a color representation that separates the luminance (grayscale) (Y) component from the chroma components, which are Cb (blue difference) and Cr (red difference)
	- By separating grayscale values, systems can selectively remove color in a manner that is less visible to the eye, improving data compression 
### What are other examples of kernels like this? 
- This usage is common in numerical computing (e.g., GPU kernels) and scientific computing libraries (e.g., BLAS routines in NumPy)
## Input
```bash
python convertRBG.py -i input_image.jpeg -o output_image.jpeg
```
## Output
> Similarity Check: `<number_of_identical_bytes>`, Different Bytes: `<number_of_bytes_different>`  
> Converted `<total_pixels>` pixels with the C kernel in `<C-kernel-time>` seconds and with the Python code in `<Python-conversion-time-in-seconds>`
- number of identical YCbCr bytes from the Python and C versions
- Number of different bytes (per pixel should be $\le 1$)
- total pixels ($width*height$)
- time to call C-kernel and return data as a float with 6 digits of precision 
- time to convert RBG to TCbCr and return the result in the python function 
# C Method
## Code
```c
void convert_to_YCrCb(unsigned char *rgb_pixels, unsigned char  
*ycc_pixels, int width, int height) {
...
}
```
## Troubleshoot
- [x] rgb_pixels is an arr of chars? but it contains "pixels"
	- size is $\text{width}*\text{height}*3$ , therefore must dereference like `r = arr[i*j ]` `g = arr[(i*j)+1]` etc. 
- [ ] In the case of C kernels, results of floating point operations from one language don't match the C version - rounding differences, conversion from integer to float and back, order of operations, etc.
	- any difference in pixel value should be $\le 1$ 
# Python Method
## Code
```python 
def convert_RGB_to_YCbCr(rgb_pixels, width, height): 
    ycc_pixels = bytearray(width * height * 3)
    for i in range(len(ycc_pixels)): 
        ycc_pixels[i] = rgb_to_ycbcr(rgb_pixels[i])

    return ycc_pixels
```
## Troubleshoot
- [ ] Output
	- [ ] number of identical YCbCr bytes from the Python and C versions
	- [ ] Number of different bytes (per pixel should be $\le 1$)
	- [ ] total pixels ($width*height$)
	- [ ] time to call C-kernel and return data as a float with 6 digits of precision 
	- [ ] time to convert RBG to TCbCr and return the result in the python function 
- [ ] error
	- running with `python convertRGB.py -i test2-input.jpg -o test2-output.jpg`
	- error: `Error loading library: [WinError 193] %1 is not a valid Win32 application`
	- this could be because of python and opencv architecture mismatch
		- uninstalled and reinstalled opencv in the venv
	- could be because of corrupted venv
		- deleted, created new venv
		- reinstalled dependencies locally 
	- "usually happens when trying to load a shared library" 
	- **.so files only work on linux machines**
	- issue: 
		1. typo in name of function in c file
		2. running .so file on its own will cause seg fault
		3. ran with python3 instead of python 