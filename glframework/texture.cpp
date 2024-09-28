#include "texture.h"
#include "core.h"
#include "../wrapper/checkError.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& picPath, unsigned int unit) {
    mUnit = unit;
    stbi_set_flip_vertically_on_load(true); //��ת����
    unsigned char* data = stbi_load(picPath.c_str(), &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);    //��ȡͼƬ

    glGenTextures(1, &mTexture);
    glActiveTexture(GL_TEXTURE0 + mUnit);   //��������Ԫ���������Ӳ�����(Sampler)���������(Texture)
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);     //�����Դ�
    /*target:��GL״̬�����ĸ����������������
    level:��mipmap���ĸ��㼶��������(��ʱ0)
    internalformat:ϣ�����������ͼƬ���ظ�ʽ
    width��height:���տ��
    border:��ʷ����������0
    format:ԭʼͼƬ��ʽ
    type:��ͨ�����ݸ�ʽ
    pixels:��������ָ��*/
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);    //�ͷ����ݣ��Ѿ�������GPU����Ҫ��

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //��Ҫ�����ض���ͼƬ�� GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  //��Ҫ����������ͼƬ�� GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //S->U->x   uv��ֵ������0��1������
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
