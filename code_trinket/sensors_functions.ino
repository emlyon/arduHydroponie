void readWaterLevel() {
    int currentWaterLvl = getWaterLevel();

    if( currentWaterLvl != waterLvl ) {
        if( currentWaterLvl == 2 ) {
            Serial.println( "alert2" );
        }
        else if( currentWaterLvl == 1 ) {
            Serial.println( "alert1" );
        }
        else if( currentWaterLvl == 0 ) {
            Serial.println( "alert0" );
        }
    }

    waterLvl = currentWaterLvl;

    if( waterLvl == 2 ) {
        setPump( HIGH );
    }
    else if( waterLvl == 1 ) {
        setPump( activePump ? HIGH : LOW );

        for( int i = 255; i > 0; i -- ) {
            analogWrite( LED_PIN, i );
            delay( 10 );
        }
        for( int i = 0; i < 255; i ++ ) {
            analogWrite( LED_PIN, i );
            delay( 10 );
        }
    }
    else if( waterLvl == 0 ) {
        setPump( LOW );

        for( int i = 0; i < 10; i ++ ) {
            digitalWrite( LED_PIN, LOW );
            delay( 200 );
            digitalWrite( LED_PIN, HIGH );
            delay( 200 );
        }
    }
}

int getWaterLevel() {
    int lvl1 = readCapacitivePin( WATER_LVL1_PIN ) >= 3 ? 1 : 0;
    int lvl2 = readCapacitivePin( WATER_LVL2_PIN ) >= 3 ? 1 : 0;
    return lvl1 + lvl2;
}

void waterLevel0Alert() {
    if( waterLvl == 0 ) {
        Serial.println( "alert0" );
    }
}
