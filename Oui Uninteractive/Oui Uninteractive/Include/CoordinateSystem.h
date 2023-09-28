/**************************************************************************
 * @file CoordinateSystem.h
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of Coordinate System functions.
 *
 * This file contains the implementation of various functions related to a
 * coordinate system using the `Coordinates` class. These functions enable
 * the manipulation and calculation of 2D coordinates, including retrieval,
 * modification, distance calculations, and threshold checks. The `Coordinates`
 * class provides a convenient way to work with 2D points and perform common
 * operations on them.
 *
 * @see Coordinates
 *************************************************************************/

#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

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

    /**************************************************************************
     * @brief GetCoords retrieves the 2D vector coordinates stored in the Coordinates object.
     *
     * This member function allows access to the 2D vector coordinates contained within the
     * Coordinates object. It returns a Vector2D object representing the coordinates.
     *
     * @return Vector2D object containing the 2D coordinates.
     *************************************************************************/
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

    /**************************************************************************
     * @brief Move the coordinates by a specified vector.
     *
     * This function modifies the current coordinates by adding the components of the
     * specified vector to the current coordinates. It effectively moves the coordinates
     * to a new position based on the vector.
     *
     * @param vec The vector specifying the movement in each dimension.
     **************************************************************************/
    void MoveCoords(Vector2D);

    /**************************************************************************
     * @brief Calculate the Euclidean distance between this coordinates and another.
     *
     * This member function calculates the Euclidean distance between the coordinates
     * represented by this object and the coordinates passed as `Coords2`. It uses the
     * Vector2DDistance function to compute the distance.
     *
     * @param Coords2 Another set of coordinates.
     * @return The Euclidean distance between this coordinates and Coords2.
     **************************************************************************/
    float Distance(Coordinates Coords2) const;

    /**************************************************************************
     * @brief Check if the Euclidean distance between this and another coordinates exceeds a threshold.
     *
     * This member function checks whether the Euclidean distance between this coordinates
     * and the coordinates passed as `Coords2` exceeds the specified threshold value `val`.
     * It uses the Vector2DSquareDistance function for this comparison.
     *
     * @param Coords2 Another set of coordinates.
     * @param val The threshold value to compare the distance against.
     * @return True if the distance exceeds the threshold, false otherwise.
     **************************************************************************/
    bool DistanceExceedsThreshold(Coordinates Coords2, float val) const;

    /**************************************************************************
     * @brief Check if the Euclidean distance between this and another coordinates is within a threshold.
     *
     * This member function checks whether the Euclidean distance between this coordinates
     * and the coordinates passed as `Coords2` is within the specified threshold value `val`.
     * It uses the DistanceExceedsThreshold function to determine this.
     *
     * @param Coords2 Another set of coordinates.
     * @param val The threshold value to compare the distance against.
     * @return True if the distance is within the threshold, false otherwise.
     **************************************************************************/
    bool DistanceIsWithinThreshold(Coordinates Coords2, float val) const;

private:
    Vector2D Coords;
};

#endif
