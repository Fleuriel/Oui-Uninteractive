#include <Global.h>

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
    return (coordIndex == X_INDEX) ? xCoords : yCoords;
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
    xCoords = x;
    yCoords = y;
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
void Coordinates::AddCoords(bool coordIndex, float val) {
    ((coordIndex == X_INDEX) ? xCoords : yCoords) += val;
}