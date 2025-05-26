#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <esp32fota.h>

// WiFi credentials
const char* ssid = "Airtel_Ellipse Nelvana";
const char* password = "hare_krishna";

// FOTA Configuration
const char* firmware_name = "esp32-fota";
const int firmware_version = 1;  // Increment this for new versions
const bool validate_signature = true;

// Create FOTA instance
esp32FOTA FOTA(firmware_name, firmware_version, validate_signature);

// GitHub repository details
const char* github_username = "vtail-biswajit";
const char* github_repo = "esp32-fota-firmware";  // You can change this to your repo name

// URL to your firmware JSON file on GitHub
const char* manifest_url = "https://raw.githubusercontent.com/vtail-biswajit/esp32-fota-firmware/main/fota.json";

// Root CA for GitHub
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n" \
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n" \
"WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n" \
"ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n" \
"MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n" \
"h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n" \
"0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n" \
"A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n" \
"T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n" \
"B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFVu3960zZ1r9\n" \
"Y8WfMCkPThWHovfSjeTg5X2ZR1JzUoWbLxXvL1zYw==\n" \
"-----END CERTIFICATE-----\n";

void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  setup_wifi();
  
  // Configure FOTA with HTTPS
  FOTA.setManifestURL(manifest_url);
  FOTA.setCert(root_ca);  // Set root CA for HTTPS
  FOTA.printConfig();
  
  // Check for updates
  checkForUpdates();
}

void loop() {
  // Check for updates every hour (3600000 ms)
  static unsigned long lastCheck = 0;
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastCheck >= 3600000) {
    lastCheck = currentMillis;
    checkForUpdates();
  }
  
  // Your main application code here
  delay(1000);
}

void checkForUpdates() {
  Serial.println("Checking for updates...");
  bool updatedNeeded = FOTA.execHTTPcheck();
  
  if (updatedNeeded) {
    Serial.println("New firmware available, starting update...");
    FOTA.execOTA();
  } else {
    Serial.println("Running latest firmware version");
  }
}
