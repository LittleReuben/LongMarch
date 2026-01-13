#pragma once

#include <filesystem>

#include "fstream"
#include "grassland/math/math_util.h"
#include "mikktspace.h"
#include "tiny_obj_loader.h"

namespace grassland {
template <typename Scalar = float>
class Mesh {
 public:
  Mesh(size_t num_vertices = 0,
       size_t num_indices = 0,
       const uint32_t *indices = nullptr,
       const Vector3<Scalar> *positions = nullptr,
       const Vector3<Scalar> *normals = nullptr,
       const Vector2<Scalar> *tex_coords = nullptr,
       const Vector3<Scalar> *tangents = nullptr);

  size_t NumVertices() const {
    return num_vertices_;
  }

  size_t NumIndices() const {
    return num_indices_;
  }

  Vector3<Scalar> *Positions() {
    return positions_.data();
  }

  Vector3<Scalar> *Normals() {
    if (normals_.empty())
      return nullptr;
    return normals_.data();
  }

  Vector3<Scalar> *Tangents() {
    if (tangents_.empty())
      return nullptr;
    return tangents_.data();
  }

  Vector2<Scalar> *TexCoords() {
    if (tex_coords_.empty())
      return nullptr;
    return tex_coords_.data();
  }

  float *Signals() {
    if (signals_.empty())
      return nullptr;
    return signals_.data();
  }

  uint32_t *Indices() {
    return indices_.data();
  }

  int *MaterialIds() {
    if (material_ids_.empty())
      return nullptr;
    return material_ids_.data();
  }

  const Vector3<Scalar> *Positions() const {
    return positions_.data();
  }

  const Vector3<Scalar> *Normals() const {
    if (normals_.empty())
      return nullptr;
    return normals_.data();
  }

  const Vector3<Scalar> *Tangents() const {
    if (tangents_.empty())
      return nullptr;
    return tangents_.data();
  }

  const Vector2<Scalar> *TexCoords() const {
    if (tex_coords_.empty())
      return nullptr;
    return tex_coords_.data();
  }

  const float *Signals() const {
    if (signals_.empty())
      return nullptr;
    return signals_.data();
  }

  const uint32_t *Indices() const {
    return indices_.data();
  }

  const int *MaterialIds() const {
    if (material_ids_.empty())
      return nullptr;
    return material_ids_.data();
  }

  int LoadObjFile(const std::string &filename);

  int SaveObjFile(const std::string &filename) const;

  int SplitVertices();

  int MergeVertices();

  int GenerateNormals(Scalar merging_threshold = 0.8f);  // if all the face normals on a vertex's pairwise dot product
  // larger than merging_threshold, then merge them

  int InitializeTexCoords(const Vector2<Scalar> &tex_coord = Vector2<Scalar>{0.5, 0.5});

  int GenerateTangents();

  static Mesh<Scalar> Sphere(int precision_lon = 10, int precision_lat = -1);

  int MakeCollisionMesh();

  Mesh<Scalar> Transformed(const Matrix<Scalar, 3, 4> &transform) const;

  // Material data structure from OBJ/MTL
  struct MaterialData {
    std::string name;
    Vector3<Scalar> diffuse{0.8f, 0.8f, 0.8f};       // Kd
    Vector3<Scalar> specular{0.5f, 0.5f, 0.5f};      // Ks
      Vector3<Scalar> emission{0.0f, 0.0f, 0.0f};    // Ke (emissive color)
    Scalar shininess{32.0f};                         // Ns
    Vector3<Scalar> transmission{0.0f, 0.0f, 0.0f};  // Tf (transmission per channel RGB, 1.0 = opaque)
    Scalar transparency{1.0f};                       // d (alpha)
    Scalar IoR{1.0f};                                // Ni
    std::string diffuse_texture;                     // map_Kd
    std::string normal_texture;
  };

  // Get material data loaded from MTL file
  const std::vector<MaterialData>& GetMaterialData() const {
    return material_data_;
  }

 private:
  std::vector<Vector3<Scalar>> positions_;
  std::vector<Vector3<Scalar>> normals_;
  std::vector<Vector3<Scalar>> tangents_;
  std::vector<Vector2<Scalar>> tex_coords_;
  std::vector<float> signals_;
  std::vector<uint32_t> indices_;
  std::vector<int> material_ids_;  // Material ID for each triangle
  std::vector<MaterialData> material_data_;  // Material data from MTL file
  size_t num_vertices_{0};
  size_t num_indices_{0};
};

}  // namespace grassland
