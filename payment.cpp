class Payment
{
public:
    virtual void processPayment(float amount) = 0;
    virtual ~Payment() {}
};
