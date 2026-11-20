# include "payment.h"

# include <cstdio>
# include <cstdlib>
# include <cstring>

# define KEY_SIZE 128

/* Simula o gateway de pagamentos, que aceita o pagamento quando a chave foi informada e o valor é positivo. */
static bool gatewayAuthorize(const char *key, double amount)
{
    return key[0] != '\0' && amount > 0.0;
}

/* Autoriza o pagamento com a chave do gateway e apaga a chave da memória logo depois do uso. */
bool processPayment(double amount)
{
    char key[KEY_SIZE];
    const char *configured_key = getenv("PAYMENT_KEY");
    bool authorized;

    snprintf(key, sizeof key, "%s", configured_key != NULL ? configured_key : "");
    authorized = gatewayAuthorize(key, amount);
    memset(key, 0, sizeof key);
    return authorized;
}
