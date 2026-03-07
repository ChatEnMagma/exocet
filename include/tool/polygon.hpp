#pragma once

#include <ranges>
#include <vector>

#include "constantes.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    using Vertex = Vector2D<double>;
    using Vertices = std::vector<Vertex>;

    class Polygon {
        private:
            Vertices vertices;
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

                for_each(vertices.begin(), vertices.end(), [this](const auto v) {
                    this->width = std::max<int>(this->width, v.x);
                    this->height = std::max<int>(this->height, v.y);

                    this->pos.x = std::min<double>(this->pos.x, v.x);
                    this->pos.y = std::min<double>(this->pos.y, v.y);
                });
            }
            /**
             * \brief Make a polygon with lua table like {{x: 0, y: 0}, {x: 0, y: 32}, ...}
             */
            Polygon(sol::table luaVertices) {
                luaVertices.for_each([&](sol::object, sol::object const& value) { this->vertices.push_back(value.as<EngineVector2D>()); });

                this->width = 0;
                this->height = 0;
                this->pos = Vertex(0, 0);

                for_each(vertices.begin(), vertices.end(), [this](const auto v) {
                    this->width = std::max<int>(this->width, v.x);
                    this->height = std::max<int>(this->height, v.y);

                    this->pos.x = std::min<double>(this->pos.x, v.x);
                    this->pos.y = std::min<double>(this->pos.y, v.y);
                });
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
            inline Vertices getVertices() const noexcept { return vertices; }
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
            Polygon translate(const Vertex& position) const noexcept {
                auto newVertices = std::ranges::views::transform(vertices, [position](auto& v) {
                    return v + position;
                });

                return Polygon({ newVertices.begin(), newVertices.end() });
            }
            /**
             * \brief Rotate the polygon
             * \return The polygon rotated
             */
            Polygon rotate(double angle) const noexcept {
                auto rotateVertices = std::ranges::views::transform(vertices, [angle](auto& v) { 
                    return Vertex(v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle));
                });

                return Polygon({ rotateVertices.begin(), rotateVertices.end() });
            }

            Vertices::iterator begin() noexcept { return vertices.begin(); }
            Vertices::iterator end() noexcept { return vertices.end(); }

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