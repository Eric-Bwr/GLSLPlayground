#include "UiTextField.h"

UiTextField::UiTextField(char *text, float x, float y, float width, float height, Font *font, float fontSize,
                         int textPosition) {
    type = UI_TEXT_FIELD;
    this->text = new UiText(text,x,y,width,height,font,fontSize,textPosition);
    this->body = new UiRectangle(x,y,width,height,0.f,new Color("#262626"));
}

UiTextField::UiTextField(char *text, float x, float y, float width, float height, Font *font, float fontSize,
                         Color *textColor, Color *outlineColor, int textPosition) {
    type = UI_TEXT_FIELD;
    this->text = new UiText(text,x,y,width,height,font,fontSize,textPosition);
    this->body = new UiRectangle(x,y,width,height,0.f,new Color("#262626"));
}

UiTextField::UiTextField(char *text, float x, float y, float width, float height, Font *font, float fontSize,
                         Texture *texture, Color *textColor, Color *outlineColor, int textPosition){
    type = UI_TEXT_FIELD;
    this->text = new UiText(text,x,y,width,height,font,fontSize,textPosition);
    this->body = new UiRectangle(x,y,width,height,0.f,new Color("#262626"));
}

void UiTextField::charInput(unsigned int character) {

}

void UiTextField::mouseButtonInput(int button, int action, int mods) {

}

void UiTextField::mousePositionInput(double x, double y) {

}

void UiTextField::keyInput(int key, int scancode, int action, int mods) {

}