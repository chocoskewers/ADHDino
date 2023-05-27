#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN 2

#define SIDE_THRESHOLD 200
#define CENTER 512
#define CENTER_THRESHOLD 100

int ledA = 8;
int ledB = 9;
int ledC = 10;
int ledD = 11;
int ledE = 7;
int leds [5] = {ledC, ledD, ledB, ledA, ledE}; //add pin location
int sequence [100]; //generate sequence later
int roundNr; //keeps track of which round the player is in
int waitTime = 500;
bool seq = true;

int input;
int xValue = 0;
int yValue = 0;

void setup() {
    randomSeed(0);
    for (int i = 0; i < 5; i++) {
        pinMode(leds[i], OUTPUT);
    }
    pinMode(SW_PIN, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    seq = true;
    roundNr = 0;
    generateSequence();

    while (seq) {
        digitalWrite(leds[4], HIGH);
        while (digitalRead(SW_PIN) == HIGH) {
            delay(100);
        }
        digitalWrite(leds[4], LOW);
        roundNr++;
        showSequence(roundNr, sequence);
        playSequence(roundNr, sequence);
    }
}

void generateSequence() {
    for (int i = 0; i < 100; i++) {
        sequence[i] = random(4);
    }
}

void showSequence(int roundNr, int sequence[100]) {
    for (int i = 0; i < roundNr; i++) {
        delay(waitTime);
        digitalWrite(leds[sequence[i]], HIGH);
        delay(waitTime);
        digitalWrite(leds[sequence[i]], LOW);
    }
}

void playSequence(int roundNr, int sequence[100]) {
    for (int i = 0; i < roundNr; ++i) {
        input = -1;
        while (input == -1) {
            xValue = analogRead(VRX_PIN);
            yValue = analogRead(VRY_PIN);

            if (xValue < CENTER - SIDE_THRESHOLD) {
                input = 1;
            } else if (xValue > CENTER + SIDE_THRESHOLD) {
                input = 0;
            }

            if (yValue < CENTER - SIDE_THRESHOLD) {
                input = 3;
            } else if (yValue > CENTER + SIDE_THRESHOLD) {
                input = 2;
            }
        }

        digitalWrite(leds[input], HIGH);
        delay(100);
        digitalWrite(leds[input], LOW);

        if (input != sequence[i]) {
            seq = false;
            break;
        }

        while (analogRead(VRX_PIN) < CENTER - CENTER_THRESHOLD
            || analogRead(VRX_PIN) > CENTER + CENTER_THRESHOLD
            || analogRead(VRY_PIN) < CENTER - CENTER_THRESHOLD
            || analogRead(VRY_PIN) > CENTER + CENTER_THRESHOLD) {
            delay(100);
        }
    }
}