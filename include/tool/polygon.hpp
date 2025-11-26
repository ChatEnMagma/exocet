#pragma once

#include <vector>

#include "tool/vectors.hpp"

namespace exocet {
    using Vertex = Vector2D<int>;

    class Polygon {
        private:
            std::vector<Vertex> vertices;
        public:
            Polygon() { vertices = {}; }
            /**
             * \brief Make a sqare vertices
             */
            Polygon(int xpos, int ypos, int width, int height) {
                vertices = {
                    Vector2D<int>(xpos, ypos),
                    Vector2D<int>(xpos + width, ypos),
                    Vector2D<int>(xpos + width, ypos + height),
                    Vector2D<int>(xpos, ypos + height)
                };
            }
            Polygon(std::vector<Vertex> vertices) { this->vertices.assign(vertices.begin(), vertices.end()); }
            Polygon(sol::table vertices) {
                vertices.for_each([&](sol::object const& key, sol::object const& value) {
                    this->vertices.push_back(Vector2D<int>(
                        value.as<sol::table>()["x"].get<int>(),
                        value.as<sol::table>()["y"].get<int>()
                    ));
                });
            }

            /**
             * \return Get a specific point
             */
            inline Vertex getVertex(std::size_t i) const { return vertices[i]; }
            inline std::vector<Vertex> getVertices() const { return vertices; }
            inline std::size_t length() const { return vertices.size(); }
            Vector2D<int> getEdge(std::size_t i) const {
                return vertices[i] - vertices[(i + 1) % length()];
            }
            Vector2D<double> getEdgeNormal(std::size_t i) const {
                Vertex edge = getEdge(i);
                return Vector2D<double>(edge.y, -edge.x).normalized();
            }
            std::vector<Vector2D<double>> getAxes() const {
                std::vector<Vector2D<double>> axis;

                for(std::size_t i = 0; i < length(); i++) {
                    Vector2D<double> edge = (vertices[i] - vertices[(i + 1) % length()]).convert<double>();
                    axis.push_back(edge.perpendicular().normalized());
                }

                return axis;
            }

            Polygon translate(Vector2D<int> position) const {
                std::vector<Vertex> vrt = std::vector<Vertex>(length());

                for(std::size_t i = 0; i < length(); i++) {
                    vrt[i] = vertices[i] + position;
                }

                return Polygon(vrt);
            }
            Polygon rotate(double angle) const {
                Polygon poly(vertices);

                int x, y;

                for(Vertex p: poly) {
                    x = p.x;
                    y = p.y;
                    
                    p.x = x * cos(angle) - y * sin(angle);
                    p.y = x * sin(angle) + y * cos(angle);
                }

                return poly;
            }

            Polygon rotate(float angle) const {
                return Polygon();
            }

            inline std::vector<Vertex>::iterator begin() { return vertices.begin(); }
            inline std::vector<Vertex>::iterator end() { return vertices.end(); }

            inline Vector2D<int> operator[](std::size_t i) const { return getVertex(i); }

            inline friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
                os << "[";
                for(std::size_t i = 0; i < poly.length(); i++) {
                    os << poly[i];
                    if(i != poly.length() - 1)
                        os << " -> ";
                }
                return os << "]";
            }
    };
}