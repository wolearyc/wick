/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_polygon.c
 * ----------------------------------------------------------------------------
 */
#include "wic_polygon.h"
int wic_init_polygon(WicPolygon* target, WicPair location, WicPair* vertices,
                 size_t num_vertices, WicColor color)
{
    if(target == 0)
        return wic_report_error(-41);
    if(num_vertices < 3)
        return wic_report_error(-42);
    WicPair* new_vertices = malloc(sizeof(WicPair) * num_vertices);
    if(new_vertices == 0)
        return wic_report_error(-43);
    target->p_vertices = new_vertices;
    target->location = location;
    for(int i = 0; i < num_vertices; i++)
        target->p_vertices[i] = vertices[i];
    target->color = color;
    target->center = (WicPair) {0,0};
    WicPair geometric_center = {0,0};
    for(int i = 0; i < num_vertices; i++)
        geometric_center = wic_add_pairs(geometric_center, vertices[i]);
    geometric_center = wic_divide_pairs(geometric_center,
                                    (WicPair) {num_vertices, num_vertices});
    target->p_geometric_center = geometric_center;
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(0);
}
int wic_set_polygon_vertices(WicPolygon* target, WicPair* vertices, size_t num_vertices)
{
    if(target == 0)
        return wic_report_error(-44);
    if(num_vertices < 3)
        return wic_report_error(-45);
    WicPair* new_vertices = realloc(target->p_vertices,
                                 num_vertices * sizeof(WicPair));
    if(new_vertices == 0)
        return wic_report_error(-46);
    target->p_vertices = new_vertices;
    target->p_num_vertices = num_vertices;
    WicPair geometric_center = {0,0};
    for(int i = 0; i < num_vertices; i++)
    {
        target->p_vertices[i] = vertices[i];
        geometric_center = wic_add_pairs(geometric_center, vertices[i]);
    }
    geometric_center = wic_divide_pairs(geometric_center,
                                    (WicPair) {num_vertices, num_vertices});
    target->p_geometric_center = geometric_center;
    return wic_report_error(0);
}
int wic_draw_polygon(WicPolygon* target, WicGame* game)
{
    if(target == 0)
        return wic_report_error(-47);
    if(game == 0)
        return wic_report_error(-48);
    double cosine = cos(target->rotation);
    double sine = sin(target->rotation);
    wic_select_color(&(target->color));
    glBegin(GL_POLYGON);
    for(int i = 0; i < target->p_num_vertices; i++)
    {
        WicPair vertex = target->p_vertices[i];
        vertex = wic_subtract_pairs(vertex, target->center);
        vertex = wic_multiply_pairs(vertex, target->scale);
        double x = vertex.x * cosine - vertex.y * sine;
        double y = vertex.x * sine + vertex.y * cosine;
        vertex.x = x;
        vertex.y = y;
        if(!target->draw_centered)
            vertex = wic_add_pairs(vertex, target->center);
        vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                  game->p_dimensions);
        glVertex2d(vertex.x, vertex.y);
    }
    glEnd();
    return wic_report_error(0);
}
int wic_free_polygon(WicPolygon* target)
{
    if(target == 0)
        return wic_report_error(-49);
    free(target->p_vertices);
    target->p_vertices = 0;
    return wic_report_error(0);
}