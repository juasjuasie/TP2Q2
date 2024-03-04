#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

using std::vector;
using std::optional;
using std::filesystem::path;
using std::ofstream;
using std::cout;
using std::istreambuf_iterator;
using std::ifstream;

// Writes an ASCII character to the output file using carret notation (https://fr.wikipedia.org/wiki/Notation_caret)
void write_carret(const char c, ofstream &output) {
   // Base control characters (the first 32)
   if (c < 32) {
      // Add caret and offset by 64 (ASCII code for '@')
      output << '^' << static_cast<char>(c + 64);
   }
   // Special handling for DEL (ASCII code 127)
   else if (c == 127) {
      output << "^?";
   }
   // Printable characters
   else {
      output << c;
   }
}

// Encodes the message into the output file using simple bitwise XOR encryption with a cyclical key.
void encode_to_file(const vector<char> &key, const vector<char> &message, ofstream &output) {
   for (size_t i = 0; i < message.size(); i++) {
      // Encode character
      const auto message_char = message[i];
      const auto key_char = key[i % key.size()];
      const char encoded_char = static_cast<char>(message_char ^ key_char);

      // Write to output in carret notation
      write_carret(encoded_char, output);
   }
}


// Reads the content of the file at the given path as a vector of bytes.
// If the file cannot be read, an empty optional is returned.
optional<vector<char> > read_file(const path &path) {
   // If stream construction failed, return empty option.
   ifstream input_stream(path);
   if (input_stream.fail()) {
      return {};
   }
   // Otherwise, read stream into a vector and return
   vector data((istreambuf_iterator(input_stream)),
               istreambuf_iterator<char>());
   return data;
}

int main() {
   // Paths
   const path message_path = "message.txt";
   const path key_path = "clef.txt";
   const path output_path = "chiffre.txt";

   // Read message
   const auto message = read_file(message_path);
   if (!message.has_value()) {
      cout << "File " << message_path << " could not be opened\n";
      return EXIT_FAILURE;
   }

   // Read key
   const auto key = read_file(key_path);
   if (!key.has_value()) {
      cout << "File " << key_path << " could not be opened\n";
      return EXIT_FAILURE;
   }

   // Open output file
   ofstream out_file(output_path);
   if (out_file.fail()) {
      cout << "File " << output_path << " could not be opened\n";
      return EXIT_FAILURE;
   }

   // Encode into output file
   encode_to_file(key.value(), message.value(), out_file);

   return EXIT_SUCCESS;
}
