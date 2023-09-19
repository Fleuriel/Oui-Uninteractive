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

/**************************************************************************
 * @brief GetCoords retrieves the 2D vector coordinates stored in the Coordinates object.
 *
 * This member function allows access to the 2D vector coordinates contained within the
 * Coordinates object. It returns a Vector2D object representing the coordinates.
 *
 * @return Vector2D object containing the 2D coordinates.
 *************************************************************************/
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

/**
 * @brief Calculate the Euclidean distance between this coordinates and another.
 *
 * This member function calculates the Euclidean distance between the coordinates
 * represented by this object and the coordinates passed as `Coords2`. It uses the
 * Vector2DDistance function to compute the distance.
 *
 * @param Coords2 Another set of coordinates.
 * @return The Euclidean distance between this coordinates and Coords2.
 */
float Coordinates::Distance(Coordinates Coords2) const {
    return Vector2DDistance(Coords, Coords2.Coords);
}

/**
 * @brief Check if the Euclidean distance between this and another coordinates exceeds a threshold.
 *
 * This member function checks whether the Euclidean distance between this coordinates
 * and the coordinates passed as `Coords2` exceeds the specified threshold value `val`.
 * It uses the Vector2DSquareDistance function for this comparison.
 *
 * @param Coords2 Another set of coordinates.
 * @param val The threshold value to compare the distance against.
 * @return True if the distance exceeds the threshold, false otherwise.
 */
bool Coordinates::DistanceExceedsThreshold(Coordinates Coords2, float val) const {
    return (Vector2DSquareDistance(Coords, Coords2.Coords) > pow(val,2.0));
}

/**
 * @brief Check if the Euclidean distance between this and another coordinates is within a threshold.
 *
 * This member function checks whether the Euclidean distance between this coordinates
 * and the coordinates passed as `Coords2` is within the specified threshold value `val`.
 * It uses the DistanceExceedsThreshold function to determine this.
 *
 * @param Coords2 Another set of coordinates.
 * @param val The threshold value to compare the distance against.
 * @return True if the distance is within the threshold, false otherwise.
 */
bool Coordinates::DistanceIsWithinThreshold(Coordinates Coords2, float val) const {
    return !DistanceExceedsThreshold(Coords2, val);
}