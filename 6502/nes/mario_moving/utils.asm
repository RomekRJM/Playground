NextRandomByte:
  LDA randomByte
  ROL
  ROL
  ADC randomByte
  ADC #$17
  STA randomByte
  RTS

NextRandomBool:
  JSR NextRandomByte
  AND #$01
  RTS

NextRandom1or2:
  JSR NextRandomByte
  CMP #$7f
  BCC :+
    LDA #$01
    RTS
  :
  LDA #$02
  RTS
