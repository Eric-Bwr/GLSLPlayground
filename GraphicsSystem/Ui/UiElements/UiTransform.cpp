#include "UiTransform.h"

UiTransform::UiTransform() = default;

void UiTransform::updateTransforms() {
    modelMatrix.identity();
    modelMatrix.translate(positionX + additionalConstraintPaddingX + (scaleX / 2.0f), positionY + additionalConstraintPaddingY + (scaleY / 2.0f), 0);
    modelMatrix.rotate(rotationX, 1.0f, 0.0f, 0.0f);
    modelMatrix.rotate(rotationY, 0.0f, 1.0f, 0.0f);
    modelMatrix.rotate(rotationZ, 0.0f, 0.0f, 1.0f);
    modelMatrix.scale(scaleX / 2.0f, scaleY / 2.0f, 0.f);
}

void UiTransform::updateConstraints(float width, float height) {
    this->transformAreaWidth = width;
    this->transformAreaHeight = height;

    if(useWidthConstraint){
        calculateXConstraint(width);
        calculateWidthConstraint(width);
    }
    if(useXConstraint){
        calculateWidthConstraint(width);
        calculateXConstraint(width);
    }
    if(useHeightConstraint){
        calculateYConstraint(height);
        calculateHeightConstraint(height);
    }
    if(useYConstraint){
        calculateHeightConstraint(height);
        calculateYConstraint(height);
    }
}

void UiTransform::setConstraintX(float x, int constraint) {
    useXConstraint = true;
    this->xConstraint = x;
    this->xConstraintType = constraint;
}

void UiTransform::setConstraintY(float y, int constraint) {
    useYConstraint = true;
    this->yConstraint = y;
    this->yConstraintType = constraint;
}

void UiTransform::setConstraintWidth(float width, int constraint) {
    useWidthConstraint = true;
    this->widthConstraint = width;
    this->widthConstraintType = constraint;
}

void UiTransform::setConstraintHeight(float height, int constraint) {
    useHeightConstraint = true;
    this->heightConstraint = height;
    this->heightConstraintType = constraint;
}

void UiTransform::setTopPadding(float topPadding) {
    this->topPadding = topPadding;
    this->scaleY -= this->topPadding;
    updateTransforms();
}

void UiTransform::setBottomPadding(float bottomPadding) {
    this->bottomPadding = bottomPadding;
    positionY+=bottomPadding;
    scaleY -= bottomPadding * 1.5;
    updateTransforms();
}

void UiTransform::setLeftPadding(float leftPadding) {
    this->leftPadding = leftPadding;
    positionX+=leftPadding;
    scaleX -=leftPadding*1.5;
    updateTransforms();
}

void UiTransform::setRightPadding(float rightPadding) {
    this->rightPadding = rightPadding;
    scaleX -= this->rightPadding;
    updateTransforms();
}

void UiTransform::calculateXConstraint(float width) {
    if(useXConstraint){
        if(xConstraintType == PixelConstraint){
            float k = (width - scaleX) / 100.0f;
            k *= xConstraint;
            positionX = k ;
            updateTransforms();
        }
    }
}

void UiTransform::calculateYConstraint(float height) {
    if(useYConstraint){
        if(yConstraintType == PixelConstraint){
            float k = (height- scaleY) / 100.0f;
            k *= yConstraint;
            positionY = k  + bottomPadding;
            updateTransforms();
        }
    }
}

void UiTransform::calculateWidthConstraint(float width) {
    if(useWidthConstraint){
        if(widthConstraintType == PixelConstraint){
            float k = width / 100.0f;
            k *= widthConstraint;
            scaleX = k ;
            updateTransforms();
        }else if(widthConstraintType == AspectConstraint && heightConstraintType != AspectConstraint){
            float k = scaleY * widthConstraint;
            scaleX = k ;
            updateTransforms();
        }
    }
}

void UiTransform::calculateHeightConstraint(float height) {
   if(useHeightConstraint){
       if(heightConstraintType == PixelConstraint){
           float k = height / 100.0f;
           k *= heightConstraint;
           scaleY = k - topPadding - ( bottomPadding*1.5);
           updateTransforms();
       }else if(heightConstraintType == AspectConstraint && widthConstraintType != AspectConstraint){
           float k = scaleX * heightConstraint;
           scaleY = k ;
           updateTransforms();
       }
   }
}
float UiTransform::map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


