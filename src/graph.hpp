//
// Created by 73109 on 2021/5/25.
//

#ifndef IMAGE_STEGANOGRAPHY_GRAPH_HPP
#define IMAGE_STEGANOGRAPHY_GRAPH_HPP

#include <fstream>

template<int N, int M>
struct Graph {
    struct pixel {
        int R, G, B;

        pixel(int R, int G, int B) : R(R), G(G), B(B) {}

        pixel() = default;

        friend std::fstream &operator<<(std::fstream &file, const pixel &obj) {
            file << obj.R << ' ' << obj.G << ' ' << obj.B;
            return file;
        }

        friend std::fstream &operator>>(std::fstream &file, pixel &obj) {
            file >> obj.R >> obj.G >> obj.B;
            return file;
        }
    } graph[N][M];

    friend std::fstream &operator<<(std::fstream &file, const Graph &obj) {
        file << "P3\n" << N << ' ' << M << '\n';
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) {
                file << obj.graph[i][j] << ((j == M - 1) ? '\n' : ' ');
            }
        return file;
    }

    friend std::fstream &operator>>(std::fstream &file, Graph &obj) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) {
                file >> obj.graph[i][j];
            }
        return file;
    }
};


#endif //IMAGE_STEGANOGRAPHY_GRAPH_HPP
