#include "UiImage.h"

UiImage::UiImage(float x, float y, float width, float height, float angle, Texture* texture) : texture(texture) {
    setPositionX(x);
    setPositionY(y);
    setRotationZ(angle);
    setWidth(width);
    setHeight(height);
    type = UI_IMAGE;
}

void UiImage::render(WindowContainer *container) {
    container->imageShader->bind();
    if(texture != nullptr)
        texture->bind();
    container->imageShader->setUniform4f("corners",getCornerBottomLeft(),getCornerTopLeft(),getCornerTopRight(),getCornerBottomRight());
    container->imageShader->setUniform1f("smoothness", getCornerSmoothness());
    container->imageShader->setUniform1f("uiWidth", getWidth());
    container->imageShader->setUniform1f("uiHeight", getHeight());
    container->imageShader->setUniformMatrix4f("model",getModelMatrix()->getBuffer());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    if(shouldShowHitBox()) {
        container->hitBoxShader->bind();
        container->hitBoxShader->setUniformMatrix4f("model",getModelMatrix()->getBuffer());
        container->hitBoxShader->setUniform4f("color", hitBoxColor->getNormalizedDecimal().r, hitBoxColor->getNormalizedDecimal().g,hitBoxColor->getNormalizedDecimal().b, hitBoxColor->getNormalizedDecimal().a);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}
