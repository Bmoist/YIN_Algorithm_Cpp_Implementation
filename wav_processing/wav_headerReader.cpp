// Based on Razgriz's sample code from stackoverflow.
// https://stackoverflow.com/questions/13660777/c-reading-the-data-part-of-a-wav-file
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using std::fstream;
using std::string;

#define path                                                                   \
  "/Users/bmois/Documents/GitHub/YIN_Algorithm_Cpp_Implementation/"            \
  "clarinet.wav"
  
// @TODO: Revise hex to decimal conversion
typedef struct WAV_HEADER {
  unsigned char RIFF[4]; // RIFF Header      Magic header
  // unsigned long justATest;
  unsigned char FileSize[4];     // RIFF Chunk Size
  unsigned char WAVE[4];          // WAVE Header
  unsigned char fmt[4];           // FMT header
  unsigned char FormatDataLength[4]; // Size of the fmt chunk
  unsigned char AudioFormat[2];   // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM
                         // Mu-Law, 258=IBM A-Law, 259=ADPCM
  unsigned char NumOfChan[2];     // Number of channels 1=Mono 2=Sterio
  unsigned char SampleRate[4]; // Sample Rate in Hz
  unsigned char bytesPerSec[4];   // (Sample Rate * BitsPerSample * Channels) / 8
  unsigned char blockAlign[2];    // 2=16-bit mono, 4=16-bit stereo
  unsigned char bitsPerSample[2]; // Number of bits per sample
  unsigned char Subchunk2ID[4];   // "data"  string
  unsigned char Subchunk2Size[4]; // Sampled data length

} wav_hdr;

// Function prototypes
int getFileSize(FILE *inFile);

int maain(int argc, char *argv[]) {
  wav_hdr wavHeader;
  FILE *wavFile;
  int headerSize = sizeof(wav_hdr), filelength = 0;

  string answer;

  do {
    string input;
    string answer;

    const char *filePath;
    system("clear");
    system("read -n 1 -s -p \"Press any key to continue...\"");
    system("clear");

    filePath = path;

    wavFile = fopen(filePath, "r");

    if (wavFile == NULL) {
      printf("Can not able to open wave file\n");
      // exit(EXIT_FAILURE);
    }
    fread(&wavHeader, headerSize, 1, wavFile);
    filelength = getFileSize(wavFile);
    fclose(wavFile);

    puts("===============================");
    cout << "File is                    : " << filelength << " bytes." << endl;

    cout << "RIFF header                : " << hex << wavHeader.RIFF[0]
         << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;

    // cout << "RIFF header int            : " << int(wavHeader.RIFF[0])
    //      << int(wavHeader.RIFF[1]) << int(wavHeader.RIFF[2])
    //      << int(wavHeader.RIFF[3]) << endl;

    cout << "RIFF chunk size            : " << int(wavHeader.FileSize[0])
         << int(wavHeader.FileSize[1]) << int(wavHeader.FileSize[2])
         << int(wavHeader.FileSize[3]) << endl;

    cout << "WAVE header                : " << wavHeader.WAVE[0]
         << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;

    cout << "FMT                        : " << wavHeader.fmt[0]
         << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << "[end" << endl;

    cout << "Format data length." << std::endl;

    cout << "Audio Format               : " << int(wavHeader.AudioFormat[0])
         << int(wavHeader.AudioFormat[1]) << endl;

    // Display the sampling Rate form the header
    cout << "Sample rate                : " << int(wavHeader.SampleRate[0])
         << int(wavHeader.SampleRate[1]) << int(wavHeader.SampleRate[2])
         << int(wavHeader.SampleRate[3]) << endl;

    cout << "Number of channels         : " << int(wavHeader.NumOfChan[0])
         << int(wavHeader.NumOfChan[1]) << endl;

    cout << "Number of bytes per second : " << int(wavHeader.bytesPerSec[0])
         << int(wavHeader.bytesPerSec[1]) << int(wavHeader.bytesPerSec[2])
         << int(wavHeader.bytesPerSec[3]) << endl;

    cout << "Block align                : " << int(wavHeader.blockAlign[0])
         << int(wavHeader.blockAlign[1]) << endl;

    cout << "Bits per sample            : " << int(wavHeader.bitsPerSample[0])
         << int(wavHeader.bitsPerSample[1]) << endl;

    cout << "Data string                : " << wavHeader.Subchunk2ID[0]
         << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2]
         << wavHeader.Subchunk2ID[3] << endl;

    cout << "Data size                  : " << int(wavHeader.Subchunk2Size[0])
         << int(wavHeader.Subchunk2Size[1]) << int(wavHeader.Subchunk2Size[2])
         << int(wavHeader.Subchunk2Size[3]) << endl;

    cout << endl << endl << "Try something else? (y/n)";
    cin >> answer;
    // cin.get();
    cout << endl << endl;

  } while (answer == "y");

  getchar();
  return 0;
}
// find the file size
int getFileSize(FILE *inFile) {
  int fileSize = 0;
  fseek(inFile, 0, SEEK_END);

  fileSize = ftell(inFile);

  fseek(inFile, 0, SEEK_SET);
  return fileSize;
}