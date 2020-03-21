NextRandomByte:
  STA randomByte
  ROL
  ROL
  ADC randomByte
  ADC #$17
  STA randomByte
  RTS
