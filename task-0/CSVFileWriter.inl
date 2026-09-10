template<typename First, typename... Rest>
void CSVFileWriter::write(First first, Rest... rest) {
    *this->f << first;
    ((*this->f << "," << rest), ...);
    *this->f << "\n";
}