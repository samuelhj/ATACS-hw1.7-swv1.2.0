// Lokum öllum lokum í kistu
void air_base_close()
{
    digitalWrite(AIR_OUT,OFF); // Lokum aflestunarloka
    digitalWrite(AIR_IN,OFF); // Lokum inndælingarloka
    digitalWrite(TIRE_LR,OFF); // Lokum vinstra afturhjóli
    digitalWrite(TIRE_LF,OFF); // Lokum vinstra framhjóli
    digitalWrite(TIRE_RF,OFF); // lokum hægra framhjóli
    digitalWrite(TIRE_RR,OFF); // Lokum hægra afturhjóli.
    digitalWrite(AIR_OUT,ON); // Tæmum kistu
    delay(AIR_DELAY);
    digitalWrite(AIR_OUT,OFF); // Lokum út
}