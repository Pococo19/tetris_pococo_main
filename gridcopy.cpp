#include "include\block.h"
#include <iostream>
#include "include\colors.h"
#include "include\grid.h"

Grid::Grid()
{
    num_cols = 10;
    num_rows = 20;
    cell_size = 30;
    save = true;
    Initialize();
    colors = get_cell_color();
}

void Grid::Initialize()
{
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++) {
            grid[i][j] = 0;
        }
    }
}

void Grid::Print()
{
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    int cell_value = 0;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            cell_value = grid[i][j];
            DrawRectangle(j * cell_size + 11, i * cell_size + 11, cell_size - 1, cell_size - 1, colors[cell_value]);
        }
    }
}

bool Grid::outside_cell(int row, int cols)
{
    if (row >= 0 && row < num_rows && cols >= 0 && cols < num_cols)
        return false;
    return true;
}

bool Grid::is_empty_cell(int row, int cols)
{
    if (grid[row][cols] == 0)
        return true;
    return false;
}

int Grid::clear_full_rows()
{
    int completed = 0;

    for (int row = num_rows - 1; row >= 0; row--) {
        if (is_row_full(row)) {
            clear_row(row);
            completed++;
        }
        else if (completed > 0)
            move_row_down(row, completed);
    }
    return completed;
}

bool Grid::is_row_full(int row)
{
    for (int col= 0; col < num_cols; col++) {
        if (grid[row][col] == 0)
            return false;
    }
    return true;
}

void Grid::clear_row(int row)
{
    for (int col = 0; col < num_cols; col++) {
        grid[row][col] = 0;
    }
}

void Grid::move_row_down(int row, int num_rows)
{
    for (int col = 0; col < num_cols; col++)
    {
        grid[row + num_rows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

void Grid::read_file(char *filepath)
{
    char buffer[2048]; // Used to keep track of buffer size
    FILE *file = fopen(filepath, "r");
    
    if (file != NULL) {
        size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, file); // Read up to buffer size minus 1 for null termination
        buffer[bytesRead] = '\0'; // Null-terminate the string
        std::cout << buffer; // Print the buffer for debugging
        fclose(file);
    }
    int bufferIndex = 0; // Track the current position in buffer
    // Loop to fill the 2D grid array
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            // Skip non-numeric characters like spaces or newlines
            while (buffer[bufferIndex] < '0' || buffer[bufferIndex] > '9') {
                bufferIndex++;
            }
            // Assign the number from the buffer to the grid, converting char to int
            grid[i][j] = buffer[bufferIndex] - '0';
            bufferIndex++; // Move to the next character in the buffer
        }
    }
    Print(); // Print the 2D grid to verify
}
