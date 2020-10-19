#pragma once

#include <Matrix/Matrix4f.h>

#define PixelConstraint 0
#define AspectConstraint 1

class UiTransform {
public:
    UiTransform();

    virtual void updateTransforms();

    virtual void updateConstraints(float width, float height);

    inline Matrix4f *getModelMatrix() { return &modelMatrix; }

    virtual void setConstraintX(float x, int constraint);

    virtual void setConstraintY(float y, int constraint);

    virtual void setConstraintWidth(float width, int constraint);

    virtual void setConstraintHeight(float height, int constraint);

    virtual void setTopPadding(float topPadding);

    virtual void setBottomPadding(float bottomPadding);

    virtual void setLeftPadding(float leftPadding);

    virtual void setRightPadding(float rightPadding);

    virtual inline float getTransformAreaWidth() { return transformAreaWidth; }

    virtual inline float getTransformAreaHeight() { return transformAreaHeight; }

    virtual inline void setAdditionalPadding(float x, float y) {
        this->additionalConstraintPaddingX = x;
        this->additionalConstraintPaddingY = y;
    }

    inline float getAdditionalPaddingX() const { return additionalConstraintPaddingX; }

    inline float getAdditionalPaddingY() const { return additionalConstraintPaddingY; }

    virtual inline void setPosition(float x, float y) {
        this->positionX = x;
        this->positionY = y;
        updateTransforms();
    }

    virtual inline void setPositionX(float x) {
        this->positionX = x;
        updateTransforms();
    }

    virtual inline void setPositionY(float y) {
        this->positionY = y;
        updateTransforms();
    }

    virtual inline void setSize(float width, float height) {
        this->scaleX = width;
        this->scaleY = height;
        updateTransforms();
    }

    virtual inline void setWidth(float width) {
        this->scaleX = width;
        updateTransforms();
    }

    virtual inline void setHeight(float height) {
        this->scaleY = height;
        updateTransforms();
    }

    virtual inline void setRotations(float x, float y, float z) {
        this->rotationX = x;
        this->rotationY = y;
        this->rotationZ = z;
        updateTransforms();
    }

    virtual inline void setRotationX(float x) {
        this->rotationX = x;
        updateTransforms();
    }

    virtual inline void setRotationY(float y) {
        this->rotationY = y;
        updateTransforms();
    }

    virtual inline void setRotationZ(float z) {
        this->rotationZ = z;
        updateTransforms();
    }

    inline float getPositionX() const { return positionX; }

    inline float getPositionY() const { return positionY; }

    inline float getWidth() const { return scaleX; }

    inline float getHeight() const { return scaleY; }

    inline float getRotationX() const { return rotationX; }

    inline float getRotationY() const { return rotationY; }

    inline float getRotationZ() const { return rotationZ; }

    inline float getXConstraint(){return xConstraint;}
    inline float getYConstraint(){return yConstraint;}


private:
    float positionX = 0.0f, positionY = 0.0f, rotationX = 0.0f, rotationY = 0.0f, rotationZ = 0.0f, scaleX = 0.0f, scaleY = 0.0f;

    Matrix4f modelMatrix;

    float transformAreaWidth = 0;
    float transformAreaHeight = 0;

    bool useXConstraint = false;
    float xConstraint = 0.0f;
    int xConstraintType = -1;

    bool useYConstraint = false;
    float yConstraint = 0.0f;
    int yConstraintType = -1;
    bool useWidthConstraint = false;
    float widthConstraint = 0.0f;
    int widthConstraintType = -1;

    bool useHeightConstraint = false;
    float heightConstraint = 0.0f;
    int heightConstraintType = -1;

    float topPadding = 0.0f;
    float bottomPadding = 0.0f;
    float leftPadding = 0.0f;
    float rightPadding = 0.0f;

    float additionalConstraintPaddingX = 0.0f;
    float additionalConstraintPaddingY = 0.0f;

    void calculateXConstraint(float width);

    void calculateYConstraint(float height);

    void calculateWidthConstraint(float width);

    void calculateHeightConstraint(float height);

    float map(float x, float in_min, float in_max, float out_min, float out_max);
};