#pragma once

/*
 Clase: MetodoPago
 Representa un metodo de pago en el sistema.
 Gestiona el procesamiento, validacion y cancelacion de pagos.
 Genera referencias de transaccion simuladas para cada pago aprobado.
*/
class MetodoPago {
public:
    int id;             // Identificador unico del metodo de pago
    string tipo;        // Tipo de pago: "Efectivo", "Tarjeta", "Yape", etc.
    string estado;      // Estado del pago: "Pendiente", "Aprobado", "Rechazado", "Cancelado"
    double monto;       // Monto del pago en soles
    string fechaPago;   // Fecha en que se realizo el pago

    // Constructor por defecto. Inicializa el pago en estado Pendiente con monto cero.
    MetodoPago() : id(0), tipo(""), estado("Pendiente"), monto(0.0), fechaPago("") {}

    // Constructor con parametros. Recibe id, tipo, monto y fecha. El estado inicia en Pendiente.
    MetodoPago(int i, string t, double m, string fecha)
        : id(i), tipo(t), estado("Pendiente"), monto(m), fechaPago(fecha) {
    }

    /*
     Procesa el pago con el monto indicado.
     Valida que el monto sea positivo antes de aprobar.
     Si es valido, cambia el estado a "Aprobado" y muestra la referencia de la transaccion.
     Retorna true si el pago fue aprobado, false si el monto es invalido.
    */
    bool procesarPago(double montoPagar) {
        if (!validarMonto(montoPagar)) return false;
        estado = "Aprobado";
        monto = montoPagar;
        cout << "  [OK] Pago de S/." << montoPagar << " procesado con " << tipo << "." << endl;
        cout << "  Referencia: " << generarReferencia() << endl;
        return true;
    }

    /*
     Valida que el monto sea un valor positivo.
     Retorna true si el monto es mayor a cero, false en caso contrario.
    */
    bool validarMonto(double m) {
        if (m <= 0) {
            cout << "  [!] Monto invalido." << endl;
            return false;
        }
        return true;
    }

    /*
     Genera un codigo de referencia simulado para la transaccion.
     El codigo comienza con las 3 primeras letras del tipo de pago
     seguido de un guion y 6 digitos aleatorios.
    */
    string generarReferencia() {
        srand((unsigned int)time(0));
        string ref = tipo.substr(0, 3);
        ref += "-";
        for (int i = 0; i < 6; i++) ref += to_string(rand() % 10);
        return ref;
    }

    /*
     Cancela el pago si su estado actual es "Aprobado".
     Cambia el estado a "Cancelado" y muestra un mensaje de confirmacion.
     Si el pago no esta aprobado, muestra el estado actual y retorna false.
    */
    bool cancelarPago() {
        if (estado == "Aprobado") {
            estado = "Cancelado";
            cout << "  Pago cancelado." << endl;
            return true;
        }
        cout << "  No se puede cancelar un pago en estado: " << estado << endl;
        return false;
    }

    // Muestra en consola el tipo, estado, monto y fecha del pago
    void mostrar() {
        cout << "  Tipo    : " << tipo << endl;
        cout << "  Estado  : " << estado << endl;
        cout << "  Monto   : S/." << monto << endl;
        cout << "  Fecha   : " << fechaPago << endl;
    }
};
