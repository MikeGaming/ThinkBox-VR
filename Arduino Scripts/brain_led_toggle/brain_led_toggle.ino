unsigned long last_time = 0;

bool is3on;
bool is2on;

void setup()
{
    Serial.begin(9600);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
}

void loop()
{
    // Print a heartbeat
    if (millis() > last_time + 2000)
    {
        Serial.println("Arduino is alive!!");
        last_time = millis();
    }

    // Send some message when I receive an 'A' or a 'Z'.
    switch (Serial.read())
    {
        case '3':
            Serial.println("LED 3 activated");
            if(!is3on)
            {
              digitalWrite(3, HIGH);
              is3on = !is3on;
            }
            else if(is3on)
            {
              digitalWrite(3, LOW);
              is3on = !is3on;
            }
            break;
        case '2':
            if(!is2on)
            {
              digitalWrite(2, HIGH);
              is2on = !is2on;
            }
            else if(is2on)
            {
              digitalWrite(2, LOW);
              is2on = !is2on;
            }
            break;
    }
}