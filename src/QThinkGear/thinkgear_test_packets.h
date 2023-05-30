#ifndef THINKGEAR_TEST_PACKETS_H
#define THINKGEAR_TEST_PACKETS_H

unsigned char raw_wave[] = {
/* [SYNC]      [PLENGTH]         [PAYLOAD]        [CHKSUM] */
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x18,   0x65,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x29,   0x54,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x24,   0x59,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x10,   0x6d,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x01,   0x7c,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x11,   0x6c,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x29,   0x54,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x2d,   0x50,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x22,   0x5b,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x19,   0x64,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x1c,   0x61,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x20,   0x5d,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x27,   0x56,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x38,   0x45,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x47,   0x36,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x50,   0x2d,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x46,   0x37,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x38,   0x45,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x29,   0x54,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x25,   0x58,
   0xaa, 0xaa,   0x04,     0x80, 0x02, 0x00, 0x2a,   0x53 };
unsigned int raw_wave_len = 168;

unsigned char eeg_packet1[] = {
  0xaa, 0xaa,
  0x20,
  0x02, 0x00, /* Poor Signal */
  0x83,       /* EegValues */
  0x18,       /* EegValuesLength */
  0x00, 0x1e, 0xd7, 
  0x00, 0x29, 0x12,
  0x00, 0x08, 0xfb,
  0x00, 0x6b, 0x02,
  0x00, 0x25, 0x0b,
  0x00, 0x34, 0x21,
  0x00, 0x1d, 0x13,
  0x00, 0x1a, 0x4c, 
  0x04, 0x57, /* Attention */
  0x05, 0x4d, /* Meditation */
  0xfa
};

unsigned char eeg_packet2[] = {
  0xaa, 0xaa,
  0x20,
  0x02, 0x00,
  0x83,
  0x18,
  0x00, 0xc9, 0x79,
  0x00, 0xa9, 0x17,
  0x00, 0x07, 0xf0,
  0x00, 0x6f, 0xc4,
  0x00, 0x51, 0x19,
  0x00, 0x34, 0x7a,
  0x00, 0x09, 0xe5,
  0x00, 0x19, 0x84,
  0x04, 0x45, 
  0x05, 0x53,
  0xf2
};

unsigned char eeg_packet3[] = {
  0xaa, 0xaa,
  0x20,
  0x02, 0x00,
  0x83,
  0x18,
  0x01, 0x26, 0x13,
  0x00, 0x1f, 0xa5,
  0x00, 0x12, 0xfa,
  0x00, 0xf4, 0x8e,
  0x00, 0x2c, 0x01,
  0x00, 0x07, 0x44,
  0x00, 0x26, 0x46,
  0x00, 0x33, 0x09,
  0x04, 0x2b,
  0x05, 0x5a,
  0x28
};

unsigned int eeg_packet_len=36;

#endif // THINKGEAR_TEST_PACKETS_H
