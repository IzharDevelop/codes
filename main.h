// Membuat var type Intrger / Number
int zhar1 = 2;
int zhar2 = 3;
int zhar3 = 4;
int zhar4 = 5;
int zhar5 = 6;
int zhar6 = 7;
int zhar7 = 8;
int zhar8 = 9;
int zhar9 = 10;
int zhar10 = 11;

void setup() {
  // Func settup pin
  pinMode(zhar1, OUTPUT);
  pinMode(zhar2, OUTPUT);
  pinMode(zhar3, OUTPUT);
  pinMode(zhar4, OUTPUT);
  pinMode(zhar5, OUTPUT);
  pinMode(zhar6, OUTPUT);
  pinMode(zhar7, OUTPUT);
  pinMode(zhar8, OUTPUT);
  pinMode(zhar9, OUTPUT);
  pinMode(zhar10, OUTPUT);
}

void loop() {
  // Func Nyala bertahap 2 per 2 (lampu belakang tetap menyala)
  digitalWrite(zhar1, HIGH);
  digitalWrite(zhar2, HIGH);
  delay(500);

  digitalWrite(zhar3, HIGH);
  digitalWrite(zhar4, HIGH);
  delay(500);

  digitalWrite(zhar5, HIGH);
  digitalWrite(zhar6, HIGH);
  delay(500);

  digitalWrite(zhar7, HIGH);
  digitalWrite(zhar8, HIGH);
  delay(500);

  digitalWrite(zhar9, HIGH);
  digitalWrite(zhar10, HIGH);
  delay(500);

  // Func Matikan semua lampu sekaligus setelah nyala semua
  digitalWrite(zhar1, LOW);
  digitalWrite(zhar2, LOW);
  digitalWrite(zhar3, LOW);
  digitalWrite(zhar4, LOW);
  digitalWrite(zhar5, LOW);
  digitalWrite(zhar6, LOW);
  digitalWrite(zhar7, LOW);
  digitalWrite(zhar8, LOW);
  digitalWrite(zhar9, LOW);
  digitalWrite(zhar10, LOW);
  delay(500);
}
