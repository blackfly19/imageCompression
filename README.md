# imageCompression

An image compression program which compresses images by color quantization.
Color quantization means reducing the color space.

I have implemented this by using KMeans - an unsupervised machine learning algorithm.

If you want to use it

1) Install opencv

2) Clone the repository. After cloning the repository make the files using the command cmake .

3) Then use make to compile the program.

4) After this implement the code using ./imageCompress <compress/decompress> <image file/text file>

Note: This does not work on jpeg images since it uses a lossy compression algorithm. It works on .png and .bmp.
