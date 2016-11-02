#include <vle/value/Value.hpp>
#include <vle/devs/Dynamics.hpp>

namespace vd = vle::devs;
namespace vv = vle::value;

namespace examples {

    class SystemLotkaVolterra : public vd::Dynamics
    {
        double X, Y;
        double alpha, beta, gamma, delta;
        double step;

    public:
        SystemLotkaVolterra(const vd::DynamicsInit& init,
                            const vd::InitEventList& events)
            : vd::Dynamics(init, events)
        {
            // If an experimental condition called X0 exist,
            // we transform the value into a double and
            // we assign this value to X. Otherwise we
            // use a default value equal to 10.
            if (events.exist("X0"))
                X = events.getDouble("X0");
            else
                X = 10.;

            // The same behaviour for Y0.
            if (events.exist("Y0"))
                Y = events.getDouble("Y0");
            else
                Y = 10.;

            // The experimental condition alpha, beta, gamma
            // and delta must exist in the experimental
            // conditions.
            alpha = events.getDouble("alpha");
            beta = events.getDouble("beta");
            gamma = events.getDouble("gamma");
            delta = events.getDouble("delta");

            step = 0.00001;
        }

        virtual ~SystemLotkaVolterra()
        {}

        virtual vd::Time init(const vd::Time& /*time*/)
        {
            return 0.0;
        }

        virtual vd::Time timeAdvance() const
        {
            return step;
        }

        virtual void internalTransition(const vd::Time& /*time*/)
        {
            double dxdt = ((X * alpha) - (beta * X * Y));
            double dydt = (- (gamma * Y) + (delta * X * Y));

            X += step * dxdt;
            Y += step * dydt;
        }

        virtual vv::Value* observation(const vd::ObservationEvent& event) const
        {
            if (event.onPort("X"))
                return new vle::value::Double(X);
            else if (event.onPort("Y"))
                return new vle::value::Double(Y);
            else
                return vle::devs::Dynamics::observation(event);
        }
    };

} // namespace vle example

DECLARE_DYNAMICS(examples::SystemLotkaVolterra)

