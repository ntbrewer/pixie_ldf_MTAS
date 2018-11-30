# do not touch this part
INPUT = {}  # ne pas toucher

# stores the title information you wish displayed
INPUT["Title Name"] = "96Rb Cycle=0.35, 0.335, 10.0"
# stores the half life in seconds of the isotope in question
INPUT["Half Life"] = 0.203
# stores the cycle length in seconds
# this is: Collection time + 2*(move time) + measure time + laser time
COLLECTION_TIME = 0.350
TRANSPORT_TIME = 0.335
MTAS_MEASURE_TIME = 10.00
LASER_TIME = 0.2
INPUT["Cycle Length"] = (COLLECTION_TIME + TRANSPORT_TIME + MTAS_MEASURE_TIME + TRANSPORT_TIME + LASER_TIME)
# stores the collection time in seconds
INPUT["Collection Time"] = COLLECTION_TIME
# stores the rampdown time of the high voltage kicker, lets the script account
# for the fact that beam collection does not start at the beginning of the
# collection time but instead after the voltage has ramped down enough for the
# beam to hit the tape
INPUT["Voltage Rampdown Time"] = 0.002
# stores the time the HPGe spectrum was accumulating, in seconds
#INPUT["HPGe Integration Time"] = 901.0
INPUT["HPGe Integration Time"] = 2244.0 - 901.0
# stores the energies (in MeV) of the gammas of interest
INPUT["Gamma Energies"] = [0.692, 0.815, 1.0373]
# stores the intensities of the gammas of interest
# if the intensity is 2.56% give 0.0256
INPUT["Gamma Branchings"] = [0.08268, 0.78, 0.06552]
# stores the counts of the peaks of interest
#INPUT["Gamma Areas"] = [269.0, 2762.0, 221.0]
INPUT["Gamma Areas"] = [594.0-269.0, 5551.0-2762.0, 312.0-221.0]
# stores the parameters of the efficiency function
# the function is:
# eff(En) = (a0 + a1*x + a2*x^2 + a3*x^3 + a5*x^5 + a7*x^7)/(En)
# with x = Log_10(en) and En = (Gamma Energy in MeV)
# the format is: [a0, a1, a2, a3, a4, a5]
INPUT["HPGe Efficiency Function"] = [8.17090e-03, 1.84907e-03, -3.28729e-04,
                                     -7.60215e-04, 1.87004e-04, -1.16447e-05]
