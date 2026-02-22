#pragma once

#include <vector>

#include "tool/vectors.hpp"

namespace exocet {
    using Vertex = DoubleVector2D;
    using Vertices = std::vector<Vertex>;

    class Polygon {
        private:
            std::vector<Vertex> vertices;
            Vertex pos;
            int width, height;
        public:
            Polygon() noexcept {
                vertices = Vertices();

                this->width = 0;
                this->height = 0;
                this->pos = Vertex(0, 0);
            }
            /**
             * \brief Make a rectangular shape
             */
            Polygon(int xpos, int ypos, int width, int height) noexcept {
                vertices = {
                    Vertex(xpos, ypos),
                    Vertex(xpos + width, ypos),
                    Vertex(xpos + width, ypos + height),
                    Vertex(xpos, ypos + height)
                };

                this->width = width;
                this->height = height;
                this->pos = Vertex(xpos, ypos);
            }
            /**
             * \brief Make a new polygon
             */
            Polygon(Vertices vertices) noexcept {
                this->vertices.assign(vertices.begin(), vertices.end());

                this->width = 0;
                this->height = 0;

                for(Vertex v: this->vertices) {
                    this->width = std::max<int>(this->width, v.x);
                    this->height = std::max<int>(this->height, v.y);

                    this->pos.x = std::min<double>(this->pos.x, v.x);
                    this->pos.y = std::min<double>(this->pos.y, v.y);
                }
            }
            /**
             * \brief Make a polygon with lua table like {{x: 0, y: 0}, {x: 0, y: 32}, ...}
             */
            Polygon(sol::table vertices) {
                vertices.for_each([&](sol::object, sol::object const& value) { this->vertices.push_back(value.as<LuaVector2D>()); });

                this->width = 0;
                this->height = 0;
                this->pos = Vertex(0, 0);

                for(Vertex v: this->vertices) {
                    this->width = std::max<int>(this->width, v.x);
                    this->height = std::max<int>(this->height, v.y);

                    this->pos.x = std::min<double>(this->pos.x, v.x);
                    this->pos.y = std::min<double>(this->pos.y, v.y);
                }
            }
            ~Polygon() noexcept = default;

            inline Vertex getPosition() const noexcept { return this->pos; }
            inline int getWidth() const noexcept { return this->width; }
            inline int getHeight() const noexcept { return this->height; }

            inline double getUp() const noexcept { return this->pos.y; }
            inline double getDown() const noexcept { return this->pos.y + this->height; }
            inline double getLeft() const noexcept { return this->pos.x; }
            inline double getRight() const noexcept { return this->pos.x + this->width; }

            inline Vertex getCenter() const noexcept { return Vertex(pos.x + width / 2, pos.y + height / 2); }

            /**
             * \return Get a specific vertex
             */
            Vertex getVertex(std::size_t i) const {
                if(i > size()) throw std::runtime_error("overflow");
                return vertices.at(i);
            }
            /**
             * \return Get all vertices
             */
            inline std::vector<Vertex> getVertices() const noexcept { return vertices; }
            /**
             * \return The number of vertices
             */
            inline std::size_t size() const noexcept { return vertices.size(); }
            Vertex getEdge(std::size_t i) const noexcept {
                return vertices[i] - vertices[(i + 1) % size()];
            }
            Vertex getEdgeNormal(std::size_t i) const  noexcept {
                Vertex edge = getEdge(i);
                return Vector2D<double>(edge.y, -edge.x).normalized();
            }
            std::vector<Vertex> getAxes() const noexcept {
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
            Polygon translate(Vertex position) const noexcept {
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
            Polygon rotate(double angle) const noexcept {
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

            std::vector<Vertex>::iterator begin() noexcept { return vertices.begin(); }
            std::vector<Vertex>::iterator end() noexcept { return vertices.end(); }

            inline Vertex operator[](std::size_t i) const { return getVertex(i); }

            inline friend std::ostream& operator<<(std::ostream& os, const Polygon& poly) noexcept {
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