#include <fstream>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <sstream>

using namespace std;


template <typename DataType>
class Matrix {
public:
    Matrix() {}
    Matrix(std::size_t N) {
        nums = std::vector<std::vector<DataType> >(N, std::vector<DataType>(N, 0));
    }
    Matrix(std::vector<std::vector<DataType> > nums) : nums(nums) {}

    vector<vector<DataType> > get_data() const {
        return nums;
    }

    static Matrix<DataType> read_from_file(string filename, int size, int type) {
        fstream myfile(filename);
        if (myfile.is_open()) {
            string typeline;
            string blank_line;
            getline(myfile, typeline);
            getline(myfile, blank_line); 
            
            vector<vector<DataType> > data;
            for (size_t i = 0; i < size*2; ++i) {
                string line; 
                if (getline(myfile, line)) {
                    stringstream ss(line);
                    vector<DataType> row;
                    DataType value;

                    while(ss >> value) {
                        row.push_back(value);
                    } 

                    data.push_back(row);
                }
            }
            myfile.close();
            return Matrix<DataType>(data);
        }
        return Matrix<DataType>();
    }
   
    Matrix operator+(const Matrix &rhs) const{
        std::vector<std::vector<DataType> > data;
        for (size_t i = 0; i < nums.size(); ++i) {
            vector<DataType> row;
            for (size_t j = 0; j < nums[i].size(); ++j) {
                row.push_back(nums[i][j] + rhs.nums[i][j]);
            }
            data.push_back(row);
        }
        return Matrix(data);
    }

    Matrix operator*(const Matrix &rhs) const{
        std::vector<std::vector<DataType> > data(nums.size(), vector<DataType>(nums.size(), 0));
        for (size_t i = 0; i < nums.size(); ++i){
            for (size_t j = 0; j < nums.size(); ++j){
                DataType sum = 0;
                for (size_t k = 0; k < nums.size(); ++k){
                    sum += nums[i][k] * rhs.nums[k][j];
                }
                data[i][j] = sum;
            }
        }
        return Matrix(data);
    }

    void set_value(std::size_t i, std::size_t j, DataType n){
        nums[i][j] = n;
    }

    DataType get_value(std::size_t i, std::size_t j) const{
        return nums[i][j];
    }


    DataType sum_diagonal_major() const{
    DataType diagonal_sum = 0;
    int row = 0;
    int col = 0;
    while (row < nums.size() && col < nums.size()){
        diagonal_sum += nums[row][col];
        row++;
        col++;
    }
    return diagonal_sum;
    }

    DataType sum_diagonal_minor() const{
    DataType diagonal_sum = 0;
    int row = 0;
    int col = nums.size() - 1;
    while (row < nums.size() && col >= 0){
        diagonal_sum += nums[row][col];
        row++;
        col--;
    }
    return diagonal_sum;
    }

    void swap_rows(std::size_t r1, std::size_t r2){
    if (r1 <= nums.size() - 1 && r2 <= nums.size() - 1 && r1 > 0 && r2 > 0){
    vector<DataType> temp = nums[r1];
    nums[r1] = nums[r2];
    nums[r2] = temp;
    }
    else{
        cout << "Index Out of Bounds" << endl;
    }
    }

    void swap_cols(std::size_t c1, std::size_t c2){
        if (c1 <= nums.size()-1 && c2 <= nums.size()-1 && c1 > 0 && c2 > 0){
        vector<DataType> temp_values;
        for (int rows = 0; rows < nums.size(); rows++){
            temp_values.push_back(nums[rows][c1]);
        }
        for (int rows = 0; rows < nums.size(); rows++){
            nums[rows][c1] = nums[rows][c2];
        }
        for (int rows = 0; rows < nums.size(); rows++){
            nums[rows][c2] = temp_values[rows];
        }
    }
    else{
        cout << "Index Out of Bounds" << endl;
    }
    }

    void print_matrix() const{
        for (size_t i = 0; i < nums.size(); ++i) {
            for (size_t j = 0; j < nums[i].size(); ++j) {
                cout << nums[i][j] << " ";
            }
            cout << endl;
        }
    }

    void update_matrix(std::size_t i, std::size_t j, DataType new_val) {
        if (i < nums.size() && j < nums[i].size()) {
            nums[i][j] = new_val;
        } else {
            cout << "Index out of range" << endl;
        }
    }

private:
    std::vector<std::vector<DataType> > nums;  // Member variable to store the matrix
};

    vector<string> get_size_and_type(string filename){
        vector<string> vals;
        fstream myfile (filename);
        if (myfile.is_open()){
            string line;
            if (getline(myfile, line)){
                stringstream ss(line);
                string val;
                while(ss >> val){
                        vals.push_back(val);
                    } 
               }
        }
        return vals;
    }

int main() {
    // 1. Read values from a file into the matrix
    string file;
    cout << "What is the name of the file: ";
    cin >> file;

    vector<string> size_and_type = get_size_and_type(file);

    int size = stoi(size_and_type[0]);
    int type = stoi(size_and_type[1]);


    Matrix<int> mat1, mat2;
    Matrix<double> mat1_double, mat2_double;

    if (type == 0) {
        Matrix<int> m = Matrix<int>::read_from_file(file, size, type);
        vector<vector<int> > combined_values = m.get_data();
        int halfway = combined_values.size() / 2;

        // store the two matrices properly
        vector<vector<int> > m1(combined_values.begin(), combined_values.begin() + halfway);
        vector<vector<int> > m2(combined_values.begin() + halfway, combined_values.end());

        mat1 = Matrix<int>(m1);
        mat2 = Matrix<int>(m2);
    } else {
        Matrix<double> m = Matrix<double>::read_from_file(file, size, type);
        vector<vector<double> > combined_values = m.get_data();
        int halfway = combined_values.size() / 2;

        // store the two matrices properly
        vector<vector<double> > m1(combined_values.begin(), combined_values.begin() + halfway);
        vector<vector<double> > m2(combined_values.begin() + halfway, combined_values.end());

        mat1_double = Matrix<double>(m1);
        mat2_double = Matrix<double>(m2);
    }

    // print two matrices to ensure proper object creation
    if (type == 0) {
        mat1.print_matrix();
        cout << endl;
        mat2.print_matrix();
        cout << endl;

        // 2. Add two matrices and display the result
        Matrix<int> mat3 = mat1 + mat2;
        mat3.print_matrix();
        cout << endl;

        // 3. Multiply two matrices and display the result
        Matrix<int> mat4 = mat1 * mat2;
        mat4.print_matrix();
        cout << endl;

        // 4. Get the sum of matrix diagonal elements
        cout << mat1.sum_diagonal_major() + mat1.sum_diagonal_minor() << endl;
        cout << endl;

        // 5. Swap matrix rows and display the result
        mat1.swap_rows(1, 2); // swap row indices 1 and 2
        mat1.print_matrix();
        cout << endl;

        // 6. Swap matrix columns and display the result
        mat2.swap_cols(1, 2); // swap column indices 1 and 2
        mat2.print_matrix();
        cout << endl;

        // 7. Update matrix rows and display the result
        mat1.update_matrix(1, 2, 17); // update row index 1, column index 2, of matrix 1 to 17
        mat1.print_matrix();
    } else {
        mat1_double.print_matrix();
        cout << endl;
        mat2_double.print_matrix();
        cout << endl;

        // 2. Add two matrices and display the result
        Matrix<double> mat3 = mat1_double + mat2_double;
        mat3.print_matrix();
        cout << endl;

        // 3. Multiply two matrices and display the result
        Matrix<double> mat4 = mat1_double * mat2_double;
        mat4.print_matrix();
        cout << endl;

        // 4. Get the sum of matrix diagonal elements
        cout << mat1_double.sum_diagonal_major() + mat1_double.sum_diagonal_minor() << endl;
        cout << endl;

        // 5. Swap matrix rows and display the result
        mat1_double.swap_rows(1, 2); // swap row indices 1 and 2
        mat1_double.print_matrix();
        cout << endl;

        // 6. Swap matrix columns and display the result
        mat2_double.swap_cols(1, 2); // swap column indices 1 and 2
        mat2_double.print_matrix();
        cout << endl;

        // 7. Update matrix rows and display the result
        mat1_double.update_matrix(1, 2, 17.7); // update row index 1, column index 2, of matrix 1 to 17
        mat1_double.print_matrix();
    }

    return 0;
}


