#include <CoordinateSystem.h>
#include <cmath>

/**************************************************************************
 * @brief Get the specified coordinate value.
 *
 * This function returns either the x-coordinate or the y-coordinate of the
 * Coordinates object based on the provided coordinate index.
 *
 * @param coordIndex A boolean flag indicating which coordinate to retrieve.
 *                   Use `true` for the x-coordinate and `false` for the
                     y-coordinate.
 * @return The requested coordinate value as a float.
 *************************************************************************/
float Coordinates::GetCoords(bool coordIndex) const {
    return (coordIndex == X_INDEX) ? Coords.x : Coords.y;
}

Vector2D Coordinates::GetCoords() const {
    return Coords;
}

/**************************************************************************
 * @brief Set the coordinates to the specified values.
 *
 * This function allows you to set both the x and y coordinates of the Coordinates
 * object to the specified values.
 *
 * @param x The new x-coordinate value.
 * @param y The new y-coordinate value.
 *************************************************************************/
void Coordinates::SetCoords(float x, float y) {
    Coords = Vector2D(x, y);
}

/**************************************************************************
 * @brief Add a value to the specified coordinate.
 *
 * This function allows you to add a value to either the x or y coordinate
 * of the Coordinates object.
 *
 * @param coordIndex A boolean flag indicating the coordinate to modify.
 *                   Use `true` for the x-coordinate and `false` for the
 *                   y-coordinate.
 * @param val        The value to add to the selected coordinate.
 *************************************************************************/
void Coordinates::MoveCoords(bool coordIndex, float val) {
    ((coordIndex == X_INDEX) ? Coords.x : Coords.y) += val;
}

float Coordinates::Distance(Coordinates Coords2) {
    return Vector2DDistance(Coords, Coords2.Coords);
}

float Coordinates::SquareDistance(Coordinates Coords1, Coordinates Coords2) {
    return Vector2DSquareDistance(Coords1.Coords, Coords2.Coords);
}

bool Coordinates::DistanceExceedsThreshold(Coordinates Coords2, float val) {
    return (SquareDistance(*this, Coords2) > pow(val,2.0));
}

bool Coordinates::DistanceIsWithinThreshold(Coordinates Coords2, float val) {
    return !DistanceExceedsThreshold(Coords2, val);
}