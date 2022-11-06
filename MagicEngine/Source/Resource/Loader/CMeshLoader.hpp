#ifndef _MAGIC_C_MESH_LOADER_HPP_
#define _MAGIC_C_MESH_LOADER_HPP_

#include "IResourceLoader.h"
#include "../CMesh.h"

#include <fstream>
#include <vector>

using namespace std;

namespace Magic
{
    class CMeshLoader : public IResourceLoader
    {
    public:
        bool Load(const char *filePath, IResource *resource)
        {
            CMesh *mesh = (CMesh *)resource;
            if (mesh)
            {
                ifstream in(filePath, ifstream::binary);
                int vertexCount;
                int attrBit;
                in.read(reinterpret_cast<char *>(&vertexCount), sizeof(vertexCount));
                in.read(reinterpret_cast<char *>(&attrBit), sizeof(attrBit));

                std::vector<Vector3f> vertices;
                std::vector<Vector3f> normals;
                std::vector<Vector3f> colors;
                std::vector<Vector2f> uvs;
                for (int i = 0; i < vertexCount; ++i)
                {
                    if (attrBit & CMesh::AttributeBit::Vertex)
                    {
                        Vector3f vertex;
                        in.read(reinterpret_cast<char *>(&vertex), sizeof(vertex));
                        vertices.push_back(vertex);
                    }
                    if (attrBit & CMesh::AttributeBit::Normal)
                    {
                        Vector3f normal;
                        in.read(reinterpret_cast<char *>(&normal), sizeof(normal));
                        normals.push_back(normal);
                    }
                    if (attrBit & CMesh::AttributeBit::Color)
                    {
                        Vector3f color;
                        in.read(reinterpret_cast<char *>(&color), sizeof(color));
                        colors.push_back(color);
                    }
                    if (attrBit & CMesh::AttributeBit::UV)
                    {
                        Vector2f uv;
                        in.read(reinterpret_cast<char *>(&uv), sizeof(uv));
                        uvs.push_back(uv);
                    }
                }


                if (vertices.size() > 0)
                    mesh->SetVertices(vertices.data(), vertices.size() * sizeof(Vector3f));
                if (normals.size() > 0)
                    mesh->SetNormals(normals.data(), normals.size() * sizeof(Vector3f));
                if (colors.size() > 0)
                    mesh->SetColors(colors.data(), colors.size() * sizeof(Vector3f));
                if (uvs.size() > 0)
                    mesh->SetUVs(uvs.data(), uvs.size() * sizeof(Vector2f));

                int indexCount;
                vector<int>indices;
                in.read(reinterpret_cast<char *>(&indexCount), sizeof(indexCount));
                for (int i = 0; i < indexCount; ++i)
                {
                    int index;
                    in.read(reinterpret_cast<char *>(&index), sizeof(index));
                    indices.push_back(index);
                }

                if (indices.size() > 0)
                    mesh->SetIndices(indices.data(), indices.size() * sizeof(float));
                in.close();
                return true;
            }
            return false;
        }

        bool Save(const char *filePath, IResource *resource)
        {
            CMesh *mesh = (CMesh *)resource;
            if (mesh)
            {
                auto vertexCount = mesh->GetVertexCount();
                auto indexCount = mesh->GetIndexCount();
                auto vertices = mesh->GetVertices();
                auto normals = mesh->GetNormals();
                auto colors = mesh->GetColors();
                auto uvs = mesh->GetUVs();
                auto indices = mesh->GetIndices();
                auto attrBit = mesh->GetAttributeBit();

                ofstream o(filePath, ios::binary);

                o.write(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
                o.write(reinterpret_cast<char*>(&attrBit), sizeof(attrBit));

                for (int i = 0; i < vertexCount; ++i)
                {
                    if (vertices)
                    {
                        auto vertex = *(vertices + i);
                        o.write(reinterpret_cast<char*>(vertex.v), sizeof(vertex.v));
                    }
                    if (normals)
                    {
                        auto normal = *(normals + i);
                        o.write(reinterpret_cast<char*>(normal.v), sizeof(normal.v));
                    }
                    if (colors)
                    {
                        auto color = *(colors + i);
                        o.write(reinterpret_cast<char*>(color.v), sizeof(color.v));
                    }

                    if (uvs)
                    {
                        auto uv = *(uvs + i);
                        o.write(reinterpret_cast<char*>(uv.v), sizeof(uv.v));
                    }
                }

                o.write(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

                for (int i = 0; i < indexCount; ++i)
                {
                    auto index = *(indices + i);
                    o.write(reinterpret_cast<char*>(&index), sizeof(index));
                }
                o.close();
                return true;
            }
            return false;
        }
    };
}

#endif