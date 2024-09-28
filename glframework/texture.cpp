#include "texture.h"
#include "core.h"
#include "../wrapper/checkError.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& picPath, unsigned int unit) {
    mUnit = unit;
    stbi_set_flip_vertically_on_load(true); //反转坐标
    unsigned char* data = stbi_load(picPath.c_str(), &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);    //读取图片

    glGenTextures(1, &mTexture);
    glActiveTexture(GL_TEXTURE0 + mUnit);   //激活纹理单元：用于链接采样器(Sampler)与纹理对象(Texture)
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);     //开辟显存
    /*target:给GL状态机的哪个插槽纹理输送数据
    level:给mipmap的哪个层级输送数据(暂时0)
    internalformat:希望纹理对象中图片像素格式
    width，height:最终宽高
    border:历史遗留，总是0
    format:原始图片格式
    type:单通道数据格式
    pixels:数据数组指针*/
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);    //释放数据，已经发给了GPU不需要了

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //需要的像素多于图片的 GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  //需要的像素少于图片的 GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //S->U->x   uv的值超过【0，1】区间
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);   //T->V->yGL_MIRRORED_REPEAT
}

Texture::~Texture() {
    if (mTexture != 0) {
        glDeleteTextures(1, &mTexture);
    }
};


void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + mUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}
