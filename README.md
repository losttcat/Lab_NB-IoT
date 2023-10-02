# Lab_NB-IoT

### bg77_at()

    String StarterKitNB::bg77_at(char *at, uint32_t timeout, bool print)
    

Funcion predeterminada que permite la comunicacion serial para utilizar comandos AT al modulo BG77

Return -> Respuesta del comando AT

Ejemplo:

    bg77_at((char *)"AT+QGPSCFG=\"priority\",1", 500);  // Da prioridad a la antena LTE
    delay(500);

### UserAPN()

    void StarterKitNB::UserAPN(String apn, String user, String password);
    
Funcion que permite definir las credenciales de la red al dispositivo a NB

Return -> None

Ejemplo: 

    String apn = "insertyoutapn.here.cl"; //private apn
    String user = "1";
    String password = "1";

    void setup() {

      sk.Setup(true);   // Se setea la configuracion para la libreria
      delay(1000);
      sk.UserAPN(apn, user, password);
      delay(1000);
    }
    
### Connect()

    void StarterKitNB::Connect(String apn, String band = "B28 LTE, B2 LTE", String network = "NB");
    
Funcion que permite conectar al dispositivo a NB

Return -> None

Ejemplo: 

    String apn = "insertyoutapn.here.cl"; //private apn

    void setup() {

      sk.Setup(true);   // Se setea la configuracion para la libreria
      delay(1000);
      sk.Connect(apn, band, Network);  // Se conecta a NB
      delay(1000);
    }


### Reconnect()

    void StarterKitNB::Reconnect(String apn, String band = "B28 LTE, B2 LTE", String network = "NB");

Funcion que espera cierto tiempo para verificar si vuelta la conexion a NB, sino sucede se conecta nuevamente

Return -> None

Ejemplo:

    if (!sk.ConnectionStatus()) // Si no hay conexion a NB
    {
      sk.Reconnect(apn, band, Network);  // Se intenta reconecta
      delay(2000);
    }

### ConnectionStatus()

    bool StarterKitNB::ConnectionStatus()

Funcion que verifica si se encuentra conectado el dispositivo a NB

Permite obtener el estado de la conexión y hacer uso de su valor booleano para su reconexión

Return -> true si se encuentra conectado, false si no


### ConnectBroker()

    void StarterKitNB::ConnectBroker(String clientIdBr, String usernameBr, String passwordBr, int clientIdMQTT, String broker, int port, bool SSL, String cacert, String clientCert, String clientKey, int MRT_OPEN, int MRT_CONN)

Funcion que abre la red para el cliente y lo conecta a ThingsBoard

Return -> None

    // Thingsboard
    String ClientIdTB = "yourclientID";
    String usernameTB = "yourusername";
    String passwordTB = "yourpassword";

    String apn = "insertyoutapn.here.cl"; //private apn
    
    int clientIdMQTT = 2;

    void setup() {

      sk.Setup(true);   // Se setea la configuracion para la libreria
      delay(1000);
      sk.Connect(apn);  // Se conecta a NB
      delay(1000);
    }

    void loop() {
      if (!sk.ConnectionStatus()) // Si no hay conexion a NB
      {
        sk.Reconnect(apn);  // Se intenta reconecta
        delay(2000);
      }
      if (!sk.LastMessageStatus)  // Si no se ha enviado el ultimo mensaje
      {
        sk.ConnectBroker(clientID, userBroker, passwordBroker, 0, broker, port);  // Se conecta a ThingsBoard
        delay(2000);
      }
      
### SendMessage()
    
    void StarterKitNB::SendMessage(String message, String topic, int clientIdMQTT, int msgID, int qos, int retain, int MRT_PUBEX)
    
Funcion que publica (envia) un mensaje en el broker

Return -> None

Ejemplo:

      // Message
      String object = "temperature";
      String value = "37.8";
      
      sk.SendMessage(value, topic1, 0, 0, 0, 0, 10000);    // Se envia el mensaje
      delay(2000);
