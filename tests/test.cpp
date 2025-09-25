#include "gtest/gtest.h"
#include "../include/plugins.hpp"
#include "../include/im_redactor.hpp"
#include <fstream>
#include <cstdio>

void createTestBMP(const std::string& filename, int width, int length, const std::vector<RGB>& pixels)
{
    std::ofstream file(filename, std::ios::binary);

    BMPFileHeader fh;
    fh.bfType = 0x4D42;
    fh.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * length * sizeof(RGB);
    fh.bfReserved1 = 0;
    fh.bfReserved2 = 0;
    fh.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    file.write(reinterpret_cast<char*>(&fh), sizeof(fh));
    
    BMPInfoHeader ih;
    ih.biSize = sizeof(BMPInfoHeader);
    ih.biWidth = width;
    ih.biLength = length;
    ih.biPlanes = 1;
    ih.biBitCount = 24;
    ih.biCompression = 0;
    ih.biSizeImage = width * length * sizeof(RGB);
    ih.biXPelsPerMeter = 0;
    ih.biYPelsPerMeter = 0;
    ih.biClrUsed = 0;
    ih.biClrImportant = 0;
    file.write(reinterpret_cast<char*>(&ih), sizeof(ih));
    
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(RGB));
    file.close();
}

class ImageEditorTest : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            testPixels = {
                {255, 0, 0}, {0, 255, 0}, {0, 0, 255},
                {255, 255, 255}, {0, 0, 0}, {0, 255, 255},
                {255, 255, 0}, {255, 0, 255}, {0, 0, 255}
            };
            createTestBMP("test.bmp", 3, 3, testPixels);
        }
    
        void TearDown() override
        {
            std::remove("test.bmp");
            std::remove("output.bmp");
        }
    
        std::vector<RGB> testPixels;
};



TEST_F(ImageEditorTest, BMPReadInvalidFile)
{
    BMPImage image;
    EXPECT_FALSE(image.read("none_existing.bmp"));
}

TEST_F(ImageEditorTest, BMPSaveFile)
{
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    image.save("output.bmp");
    
    BMPImage savedImage;
    EXPECT_TRUE(savedImage.read("output.bmp"));
    EXPECT_EQ(savedImage.getWidth(), 3);
    EXPECT_EQ(savedImage.getLength(), 3);
}

TEST_F(ImageEditorTest, BMPSetDimensions)
{
    BMPImage image;
    image.setDimensions(4, 2);
    EXPECT_EQ(image.getWidth(), 4);
    EXPECT_EQ(image.getLength(), 2);
    
    EXPECT_THROW(image.setDimensions(-1, 5), std::invalid_argument);
}

TEST_F(ImageEditorTest, RotateClockwise)
{
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    rotateImage(image, RotationDirection::Clockwise);
    
    EXPECT_EQ(image.getWidth(), 3);
    EXPECT_EQ(image.getLength(), 3);
    
    RGB pixel = image.getPixel(0, 2);
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
}

TEST_F(ImageEditorTest, RotateCounterClockwise)
{
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    rotateImage(image, RotationDirection::CounterClockwise);
    
    RGB pixel = image.getPixel(2, 0);
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
}

TEST_F(ImageEditorTest, DoubleRotationIdentity)
{
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    BMPImage original = image;
    
    rotateImage(image, RotationDirection::Clockwise);
    rotateImage(image, RotationDirection::CounterClockwise);
    
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            EXPECT_EQ(image.getPixel(x, y).r, original.getPixel(x, y).r);
            EXPECT_EQ(image.getPixel(x, y).g, original.getPixel(x, y).g);
            EXPECT_EQ(image.getPixel(x, y).b, original.getPixel(x, y).b);
        }
    }
}

TEST_F(ImageEditorTest, GaussianFilterSmallCore)
{
    BMPImage image;
    image.setDimensions(5, 5);
    image.setPixel(2, 2, {255, 255, 255});
    
    applyGaussianFilter(image, 3, 1.0f);
    
    RGB center = image.getPixel(2, 2);
    RGB edge = image.getPixel(0, 0);
    EXPECT_GT(center.r, edge.r);
}

TEST_F(ImageEditorTest, GaussianFilterLargeSigma)
{
    BMPImage image;
    image.setDimensions(5, 5);
    image.setPixel(2, 2, {255, 255, 255});
    
    applyGaussianFilter(image, 5, 5.0f);
    
    RGB center = image.getPixel(2, 2);
    EXPECT_LT(center.r, 100);
}

TEST_F(ImageEditorTest, RotateThenFilter)
{
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    rotateImage(image, RotationDirection::Clockwise);
    applyGaussianFilter(image, 3, 1.0f);
    
    EXPECT_EQ(image.getWidth(), 3);
    EXPECT_EQ(image.getLength(), 3);
}

TEST_F(ImageEditorTest, FilterThenRotateThenSave)
{
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    applyGaussianFilter(image, 3, 1.0f);
    rotateImage(image, RotationDirection::CounterClockwise);
    image.save("output.bmp");
    
    BMPImage savedImage;
    EXPECT_TRUE(savedImage.read("output.bmp"));
    EXPECT_EQ(savedImage.getWidth(), 3);
    EXPECT_EQ(savedImage.getLength(), 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
