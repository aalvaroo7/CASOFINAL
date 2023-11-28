struct Entorno {
    std::map<std::string, Variant> variables;

    // Puedes agregar funciones o datos adicionales según sea necesario
};
namespace jsonlib {

    class Json {
    public:
        enum JsonType { Object, Array, String, Number, Boolean, Null };

        // Constructor predeterminado
        Json() : type(Null) {}

        // Constructor para valores booleanos
        Json(bool value) : type(Boolean), boolValue(value) {}

        // Constructor para números
        Json(double value) : type(Number), numberValue(value) {}

        // Constructor para cadenas
        Json(const std::string& value) : type(String), stringValue(value) {}

        // Constructor para objetos JSON
        Json(const std::map<std::string, Json>& value) : type(Object), objectValue(value) {}

        // Constructor para arrays JSON
        Json(const std::vector<Json>& value) : type(Array), arrayValue(value) {}

        // Función para convertir a cadena JSON
        std::string to_string() const;

    private:
        JsonType type;
        bool boolValue;
        double numberValue;
        std::string stringValue;
        std::map<std::string, Json> objectValue;
        std::vector<Json> arrayValue;
    };

    std::string Json::to_string() const {
        switch (type) {
            case Object: {
                std::string result = "{";
                bool first = true;
                for (const auto& pair : objectValue) {
                    if (!first) {
                        result += ",";
                    }
                    result += "\"" + pair.first + "\":" + pair.second.to_string();
                    first = false;
                }
                result += "}";
                return result;
            }
            case Array: {
                std::string result = "[";
                bool first = true;
                for (const auto& element : arrayValue) {
                    if (!first) {
                        result += ",";
                    }
                    result += element.to_string();
                    first = false;
                }
                result += "]";
                return result;
            }
            case String:
                return "\"" + stringValue + "\"";
            case Number:
                return std::to_string(numberValue);
            case Boolean:
                return boolValue ? "true" : "false";
            case Null:
                return "null";
        }
        return ""; // Nunca debería llegar aquí
    }

}  // namespace jsonlib
