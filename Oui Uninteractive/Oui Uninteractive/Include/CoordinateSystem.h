
#include <Vector2D.h>


/**************************************************************************
 * @brief A class representing 2D coordinates.
 *
 * The Coordinates class allows you to work with 2D coordinates,
 * providing methods to set, get, and modify the x and y coordinates.
 *************************************************************************/
class Coordinates {
public:

    /**************************************************************************
     * @brief Enum representing coordinate indices.
     *
     * The CoordinateSelector enum provides named constants for selecting
     * specific coordinates within a Coordinates object. It is used to
     * specify whether to access the x-coordinate or the y-coordinate.
     *************************************************************************/
    enum CoordinateSelector {
        X_INDEX, Y_INDEX
    };


    /**************************************************************************
     * @brief Constructor for the Coordinates class.
     *
     * This constructor initializes a Coordinates object with the specified
     * x and y coordinate values.
     *
     * @param x The initial x-coordinate value.
     * @param y The initial y-coordinate value.
     *************************************************************************/
    Coordinates(float x, float y) : Coords(Vector2D(x, y)) {}

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
    float GetCoords(bool coordIndex) const;


    Vector2D GetCoords() const;

    /**************************************************************************
     * @brief Set the coordinates to the specified values.
     *
     * This function allows you to set both the x and y coordinates of the Coordinates
     * object to the specified values.
     *
     * @param x The new x-coordinate value.
     * @param y The new y-coordinate value.
     *************************************************************************/
    void SetCoords(float x, float y);

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
    void MoveCoords(bool coordIndex, float val);

    float Distance(Coordinates Coords2);

    float SquareDistance(Coordinates Coords1, Coordinates Coords2);

    bool DistanceExceedsThreshold(Coordinates Coords2, float val);

    bool DistanceIsWithinThreshold(Coordinates Coords2, float val);

private:
    Vector2D Coords;
};