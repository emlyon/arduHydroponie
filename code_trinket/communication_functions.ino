void serialEvent() {
    while( Serial.available() ) {
        char inChar = ( char ) Serial.read();

        if( inChar == '\n' ) {
            parseString();
        }
        else{
            inputString += inChar;
            inputStringLength ++;
        }
    }
}

void parseString() {
    // do parsing
    if( inputString.startsWith( "getValues" ) ){
        readSensors();
        sendStates();
    }
    else if( inputString.startsWith( "setPump:" ) ) {
        char state = inputString.charAt( inputStringLength - 1 );
        if( state == '0' ){
            setPump( LOW );
            Serial.println( "OK: PUMP OFF" );
        }
        else if( state == '1' ){
            setPump( HIGH );
            Serial.println( "OK: PUMP ON" );
        }
    }
    else if( inputString.startsWith( "setWarmLight:" ) ) {
        char state = inputString.charAt( inputStringLength - 1 );
        if( state == '0' ){
            setLeds( WARM_LED_PIN, LOW );
            Serial.println( "OK: WARM LEDS OFF" );
        }
        else if( state == '1' ){
            setLeds( WARM_LED_PIN, HIGH );
            Serial.println( "OK: WARM LEDS ON" );
        }
    }
    else if( inputString.startsWith( "setColdLight:" ) ) {
        char state = inputString.charAt( inputStringLength - 1 );
        if( state == '0' ){
            setLeds( COLD_LED_PIN, LOW );
            Serial.println( "OK: COLD LEDS OFF" );
        }
        else if( state == '1' ){
            setLeds( COLD_LED_PIN, HIGH );
            Serial.println( "OK: COLD LEDS ON" );
        }
    }
    else {
        Serial.print( "CMD ERROR:" );
        Serial.println( inputString );
    }

    // reset inputString
    inputString = "";
    inputStringLength = 0;
}

void sendStates(){
    Serial.println( "waterlevel:" + String( waterLvl ) );
    Serial.println( "temp:" + String( temp ) );
    Serial.println( "light:" + String( light ) );
    Serial.println( "coldleds:" + String( coldLightIntensity ) );
    Serial.println( "warmleds:" + String( warmLightIntensity ) );
    Serial.println( "pump:" + String( pumpIntensity ) );
}