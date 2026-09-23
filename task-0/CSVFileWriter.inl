//write data to file (making sure that every string will contain the same amount of data? nah)
template<typename First, typename... Rest>
void CSVFileWriter::write(First first, Rest... rest) {
    *this->f << first;
    ((*this->f << "," << rest), ...);
    *this->f << "\n";
}
