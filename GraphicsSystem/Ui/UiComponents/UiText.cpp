#include "UiText.h"

UiText::UiText(char *text, float x, float y, float width, float height, Font *font, float fontSize, int textPosition) {
    type = UI_TEXT;
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    this->font = font;
    this->fontSize = fontSize;
    textMesh = new TextMesh();
    textMesh->processText(text, width, height, font, fontSize, textPosition);
    this->textColor = new Color("ffffff");
    this->outlineColor = new Color("B5076D");
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->textPosition = textPosition;
}

UiText::UiText(char *text, float x, float y, float width, float height, Font *font,float fontSize, Color *textColor, Color* outlineColor, int textPosition) {
    type = UI_TEXT;
    setPositionX(x);
    setPositionY(y);
    setWidth(width);
    setHeight(height);
    updateTransforms();
    this->font = font;
    this->fontSize = fontSize;
    textMesh = new TextMesh();
    textMesh->processText(text, width, height, font, fontSize, textPosition);
    this->textColor = textColor;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->textPosition = textPosition;
    this->outlineColor = outlineColor;
}

void UiText::setText(char *text) {
    this->text = text;
    textMesh->processText(text, width, height, font, fontSize, textPosition);
    if(textMesh->canReload())
        textMesh->reload();
}

void UiText::render(WindowContainer *container) {
    container->textShader->bind();
    font->getAtlas()->bind();
    container->textShader->setUniform3f("textColor", textColor->getNormalizedDecimal().r, textColor->getNormalizedDecimal().g, textColor->getNormalizedDecimal().b);
    container->textShader->setUniformMatrix4f("model", getModelMatrix()->getBuffer());
    container->textShader->setUniform1f("characterWidth", characterWidth);
    container->textShader->setUniform1f("characterEdge", characterEdge);
    if(outline){
        container->textShader->setUniformBool("hasOutline", true);
        container->textShader->setUniform1f("outlineBorderEdge", outlineBorderEdge);
        container->textShader->setUniform1f("outlineBorderWidth", outlineBorderWidth);
        container->textShader->setUniform3f("outlineColor", outlineColor->getNormalizedDecimal().r, outlineColor->getNormalizedDecimal().g, outlineColor->getNormalizedDecimal().b);
    }
    textMesh->render();
    container->textShader->setUniformBool("hasOutline", false);
    container->vao->bind();
    if(shouldShowHitBox()) {
        container->hitBoxShader->bind();
        container->hitBoxShader->setUniformMatrix4f("model", getModelMatrix()->getBuffer());
        container->hitBoxShader->setUniform4f("color", hitBoxColor->getNormalizedDecimal().r, hitBoxColor->getNormalizedDecimal().g, hitBoxColor->getNormalizedDecimal().b, hitBoxColor->getNormalizedDecimal().a);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}
