#pragma once 
#include <cmath>

struct Vec2
{
    float x;
    float y;

    // Constructors
    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}

    // Vector addition
    inline Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    // Vector subtraction
    inline Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    // Scalar multiplication
    inline Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    // Scalar division
    inline Vec2 operator/(float scalar) const {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            return Vec2(x * invScalar, y * invScalar);
        }
        return *this; // Return unchanged if division by zero
    }

    // Compound assignment operators
    inline Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline Vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    inline Vec2& operator/=(float scalar) {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            x *= invScalar;
            y *= invScalar;
        }
        return *this;
    }

    // Negation
    inline Vec2 operator-() const {
        return Vec2(-x, -y);
    }

    // Equality operators
    inline bool operator==(const Vec2& other) const {
        return (x == other.x) && (y == other.y);
    }

    inline bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }
};

struct Vec3
{
    float x;
    float y;
    float z;

    // Constructors
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const Vec2& v, float z = 0.0f) : x(v.x), y(v.y), z(z) {}

    // Vector addition
    inline Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    inline Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    inline Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    // Scalar division
    inline Vec3 operator/(float scalar) const {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            return Vec3(x * invScalar, y * invScalar, z * invScalar);
        }
        return *this; // Return unchanged if division by zero
    }

    // Compound assignment operators
    inline Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vec3& operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vec3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    inline Vec3& operator/=(float scalar) {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            x *= invScalar;
            y *= invScalar;
            z *= invScalar;
        }
        return *this;
    }

    // Negation
    inline Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }

    // Equality operators
    inline bool operator==(const Vec3& other) const {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }

    inline bool operator!=(const Vec3& other) const {
        return !(*this == other);
    }
};

// Non-member functions for Vec2

// Dot product
inline float Dot(const Vec2& a, const Vec2& b) {
    return a.x * b.x + a.y * b.y;
}

// Cross product for Vec2 (returns scalar representing area of parallelogram)
inline float Cross(const Vec2& a, const Vec2& b) {
    return a.x * b.y - a.y * b.x;
}

// Magnitude/length
inline float Length(const Vec2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// Squared length (more efficient when comparing distances)
inline float LengthSquared(const Vec2& v) {
    return v.x * v.x + v.y * v.y;
}

// Normalize vector
inline Vec2 Normalize(const Vec2& v) {
    float length = Length(v);
    if (length > 0.0f) {
        return v / length;
    }
    return v;
}

// Distance between two vectors
inline float Distance(const Vec2& a, const Vec2& b) {
    return Length(b - a);
}

// Squared distance between two vectors
inline float DistanceSquared(const Vec2& a, const Vec2& b) {
    return LengthSquared(b - a);
}

// Angle between two vectors (in radians)
inline float Angle(const Vec2& a, const Vec2& b) {
    float dot = Dot(a, b);
    float lengthProduct = Length(a) * Length(b);
    if (lengthProduct > 0.0f) {
        // Clamp to avoid floating point errors
        float cosAngle = dot / lengthProduct;
        cosAngle = std::fmax(-1.0f, std::fmin(1.0f, cosAngle));
        return std::acos(cosAngle);
    }
    return 0.0f;
}

// Linear interpolation
inline Vec2 Lerp(const Vec2& a, const Vec2& b, float t) {
    t = std::fmax(0.0f, std::fmin(1.0f, t)); // Clamp t between 0 and 1
    return a + (b - a) * t;
}

// Reflection of a vector around a normal
inline Vec2 Reflect(const Vec2& v, const Vec2& normal) {
    return v - normal * 2.0f * Dot(v, normal);
}

// Scalar multiplication (scalar * vector)
inline Vec2 operator*(float scalar, const Vec2& v) {
    return v * scalar;
}

// Non-member functions for Vec3

// Dot product
inline float Dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product
inline Vec3 Cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// Magnitude/length
inline float Length(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Squared length (more efficient when comparing distances)
inline float LengthSquared(const Vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

// Normalize vector
inline Vec3 Normalize(const Vec3& v) {
    float length = Length(v);
    if (length > 0.0f) {
        return v / length;
    }
    return v;
}

// Distance between two vectors
inline float Distance(const Vec3& a, const Vec3& b) {
    return Length(b - a);
}

// Squared distance between two vectors
inline float DistanceSquared(const Vec3& a, const Vec3& b) {
    return LengthSquared(b - a);
}

// Angle between two vectors (in radians)
inline float Angle(const Vec3& a, const Vec3& b) {
    float dot = Dot(a, b);
    float lengthProduct = Length(a) * Length(b);
    if (lengthProduct > 0.0f) {
        // Clamp to avoid floating point errors
        float cosAngle = dot / lengthProduct;
        cosAngle = std::fmax(-1.0f, std::fmin(1.0f, cosAngle));
        return std::acos(cosAngle);
    }
    return 0.0f;
}

// Linear interpolation
inline Vec3 Lerp(const Vec3& a, const Vec3& b, float t) {
    t = std::fmax(0.0f, std::fmin(1.0f, t)); // Clamp t between 0 and 1
    return a + (b - a) * t;
}

// Reflection of a vector around a normal
inline Vec3 Reflect(const Vec3& v, const Vec3& normal) {
    return v - normal * 2.0f * Dot(v, normal);
}

// Project vector a onto vector b
inline Vec3 Project(const Vec3& a, const Vec3& b) {
    float bLengthSquared = LengthSquared(b);
    if (bLengthSquared > 0.0f) {
        return b * (Dot(a, b) / bLengthSquared);
    }
    return Vec3();
}

// Scalar multiplication (scalar * vector)
inline Vec3 operator*(float scalar, const Vec3& v) {
    return v * scalar;
}
