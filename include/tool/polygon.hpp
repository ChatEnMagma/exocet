#pragma once

#include <vector>

#include "tool/vectors.hpp"

namespace exocet {
    using Vertex = LuaVector2D;

    class Polygon {
        private:
            std::vector<Vertex> vertices;
            int width, height;
        public:
            Polygon() {
                vertices = std::vector<Vertex>();

                this->width = 0;
                this->height = 0;
            }
            /**
             * \brief Make a rectangular shape
             */
            Polygon(int xpos, int ypos, int width, int height) {
                vertices = {
                    Vertex(xpos, ypos),
                    Vertex(xpos + width, ypos),
                    Vertex(xpos + width, ypos + height),
                    Vertex(xpos, ypos + height)
                };

                this->width = width;
                this->height = height;
            }
            /**
             * \brief Make a new polygon
             */
            Polygon(std::vector<Vertex> vertices) {
                this->vertices.assign(vertices.begin(), vertices.end());

                this->width = 0;
                this->height = 0;

                for(Vertex v: this->vertices) {
                    this->width = std::max<int>(this->width, v.x);
                    this->height = std::max<int>(this->height, v.y);
                }
            }
            /**
             * \brief Make a polygon with lua table like {{x: 0, y: 0}, {x: 0, y: 32}, ...}
             */
            Polygon(sol::table vertices) {
                vertices.for_each([&](sol::object const& key, sol::object const& value) {
                    this->vertices.push_back(value.as<LuaVector2D>());
                });

                this->width = 0;
                this->height = 0;

                for(Vertex v: this->vertices) {
                    this->width = std::max<int>(this->width, v.x);
                    this->height = std::max<int>(this->height, v.y);
                }
            }

            inline int getWidth() const { return this->width; }
            inline int getHeight() const { return this->height; }

            /**
             * \return Get a specific vertex
             */
            inline Vertex getVertex(std::size_t i) const { return vertices[i]; }
            /**
             * \return Get all vertices
             */
            inline std::vector<Vertex> getVertices() const { return vertices; }
            /**
             * \return The number of vertices
             */
            inline std::size_t size() const { return vertices.size(); }
            Vertex getEdge(std::size_t i) const {
                return vertices[i] - vertices[(i + 1) % size()];
            }
            Vertex getEdgeNormal(std::size_t i) const {
                Vertex edge = getEdge(i);
                return Vector2D<double>(edge.y, -edge.x).normalized();
            }
            std::vector<Vertex> getAxes() const {
                std::vector<Vertex> axis;

                for(std::size_t i = 0; i < size(); i++) {
                    Vertex edge = (vertices[i] - vertices[(i + 1) % size()]).convert<double>();
                    axis.push_back(edge.perpendicular().normalized());
                }

                return axis;
            }
            /**
             * \brief Transpose the polygon
             * \return The polygon transposed
             */
            Polygon translate(Vertex position) const {
                std::vector<Vertex> vrt = std::vector<Vertex>(size());

                for(std::size_t i = 0; i < size(); i++) {
                    vrt[i] = vertices[i] + position;
                }

                return Polygon(vrt);
            }
            /**
             * \brief Rotate the polygon
             * \return The polygon rotated
             */
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

            std::vector<Vertex>::iterator begin() { return vertices.begin(); }
            std::vector<Vertex>::iterator end() { return vertices.end(); }

            inline Vertex operator[](std::size_t i) const { return getVertex(i); }

            inline friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
                os << "[";
                for(std::size_t i = 0; i < poly.size(); i++) {
                    os << poly[i];
                    if(i != poly.size() - 1)
                        os << " -> ";
                }
                return os << "]";
            }
    };
}