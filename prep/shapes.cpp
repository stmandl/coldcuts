#include <iostream>
#include <memory>
#include <numeric>
#include <vector>
#include <cmath>

class Shape
{
public:
    virtual int GetArea() const = 0;    
};

class Rectangle : public Shape
{
private:
    int height;
    int width;

public:
    Rectangle(int height_, int width_)
     : height(height_),
       width(width_)
    {}
    
    Rectangle(Rectangle&& other) {
        height = other.height;
        width = other.width;
    }

    // Rectangle(std::unique_ptr<Rectangle>&& other) {
    //     height = other->height;
    //     width = other->width;
    // }
    
    // Rectangle(Rectangle&& other)
    // {
    //     height = other.height;
    //     width = other.width;
    // }
    
    
    int GetArea() const override
    {
        return height * width;
    }
};


int main() {
    int rectangleHeight = 0, rectangleWidth = 0;
    int triangleHeight = 0, triangleWidth = 0;
    int circleRadius = 0;

    std::cin >> rectangleHeight >> rectangleWidth >> triangleHeight >> triangleWidth >> circleRadius;

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Rectangle>(rectangleHeight, rectangleWidth));
    //shapes.emplace_back(std::make_unique<Triangle>(triangleHeight, triangleWidth));
    //shapes.emplace_back(std::make_unique<Circle>(circleRadius));

    const int totalArea = std::accumulate(shapes.begin(), shapes.end(), 0, [](int total, const auto& shape)
            { return total + shape->GetArea(); });
    std::cout << totalArea << "\n";

    return 0;
}