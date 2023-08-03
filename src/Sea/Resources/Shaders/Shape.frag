#version 450 core

#define PI 3.1415926535897932384626433832795

out vec4 FragColor;

in vec3 color;
in vec2 position;

// t: top, l: left, b: bottom, r: right;
struct ShapeProperties
{
    vec2 origin;
    vec2 size;
    vec4 color;
    float edge;
    float border_radius_tl;
    float border_radius_tr;
    float border_radius_bl;
    float border_radius_br;
};

uniform ShapeProperties shape;

vec2 corner_top_left()
{
    return vec2(shape.origin.x - shape.size.x / 2, shape.origin.y - shape.size.y / 2);
}

vec2 corner_top_right()
{
    return vec2(shape.origin.x + shape.size.x / 2, shape.origin.y - shape.size.y / 2);
}

vec2 corner_bottom_left()
{
    return vec2(shape.origin.x - shape.size.x / 2, shape.origin.y + shape.size.y / 2);
}

vec2 corner_bottom_right()
{
    return vec2(shape.origin.x + shape.size.x / 2, shape.origin.y + shape.size.y / 2);
}

bool is_corner_top_left(float radius)
{     
    vec2 corner = corner_top_left();
    vec2 mid = vec2(corner.x + radius, corner.y + radius);
    bool is_x = corner.x <= position.x && position.x <= mid.x;
    bool is_y = corner.y <= position.y && position.y <= mid.y;
    return is_x && is_y;
}

bool is_corner_top_right(float radius)
{     
    vec2 corner = corner_top_right();
    vec2 mid = vec2(corner.x - radius, corner.y + radius);
    bool is_x = corner.x >= position.x && position.x >= mid.x;
    bool is_y = corner.y <= position.y && position.y <= mid.y;
    return is_x && is_y;
}

bool is_corner_bottom_left(float radius)
{
    vec2 corner = corner_bottom_left();
    vec2 mid = vec2(corner.x + radius, corner.y - radius);
    bool is_x = corner.x <= position.x && position.x <= mid.x;
    bool is_y = corner.y >= position.y && position.y >= mid.y;
    return is_x && is_y;
}

bool is_corner_bottom_right(float radius)
{
    vec2 corner = corner_bottom_right();
    vec2 mid = vec2(corner.x - radius, corner.y - radius);
    bool is_x = corner.x >= position.x && position.x >= mid.x;
    bool is_y = corner.y >= position.y && position.y >= mid.y;
    return is_x && is_y;
}

vec4 circle(vec2 origin, vec2 position, float radius, float edge)
{
    float ds = distance(origin, position);
    float alpha = 1.0 - smoothstep(radius - edge, radius + edge, ds);
    return vec4(color, alpha);
}

void main()
{
    float alpha = shape.color.a;
    float edge = shape.edge;
    float r_top_left     = shape.border_radius_tl;
    float r_top_right    = shape.border_radius_tr;
    float r_bottom_left  = shape.border_radius_bl;
    float r_bottom_right = shape.border_radius_br;

    if (is_corner_top_left(r_top_left))
    {   
        vec2 corner = corner_top_left();
        vec2 mid = vec2(corner.x + r_top_left, corner.y + r_top_left);
        float ds = distance(mid, position.xy);
        alpha = 1.0 - smoothstep(r_top_left - edge, r_top_left + edge, ds);
    }
    else if (is_corner_top_right(r_top_right))
    {
        vec2 corner = corner_top_right();
        vec2 mid = vec2(corner.x - r_top_right, corner.y + r_top_right);
        float ds = distance(mid, position.xy);
        alpha = 1.0 - smoothstep(r_top_right - edge, r_top_right + edge, ds);
    }
    else if (is_corner_bottom_left(r_bottom_left))
    {
        vec2 corner = corner_bottom_left();
        vec2 mid = vec2(corner.x + r_bottom_left, corner.y - r_bottom_left);
        float ds = distance(mid, position.xy);
        alpha = 1.0 - smoothstep(r_bottom_left - edge, r_bottom_left + edge, ds);
    }
    else if (is_corner_bottom_right(r_bottom_right))
    {
        vec2 corner = corner_bottom_right();
        vec2 mid = vec2(corner.x - r_bottom_right, corner.y - r_bottom_right);
        float ds = distance(mid, position.xy);
        alpha = 1.0 - smoothstep(r_bottom_right - edge, r_bottom_right + edge, ds);
    }

    FragColor = vec4(shape.color.rgb, alpha);
}
