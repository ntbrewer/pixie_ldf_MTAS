# do not touch this part
INPUT = {}  # ne pas toucher

# stores the title information you wish displayed
INPUT["Title Name"] = "96Sr Decay From 96Rb In-Flight + At Collection"
# stores the half life in seconds of the isotope in question
INPUT["Half Life"] = 1.07
# stores the cycle length in seconds
# this is: Collection time + 3*(move time) + measure time + laser time
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
#INPUT["HPGe Integration Time"] = 1170.0
#INPUT["HPGe Integration Time"] = 2905.0 - 1170.0
INPUT["HPGe Integration Time"] = 285.0
# stores the energies (in MeV) of the gammas of interest
INPUT["Gamma Energies"] = [0.122297, 0.8094, 0.9317]
# stores the intensities of the gammas of interest
# if the intensity is 2.56% give 0.0256
INPUT["Gamma Branchings"] = [0.76, 0.72, 0.118]
# stores the counts of the peaks of interest
#INPUT["Gamma Areas"] = [7718.0, 2516.0, 422.0]
#INPUT["Gamma Areas"] = [18266.0-7718.0, 5824.0-2516.0, 971.0-422.0]
INPUT["Gamma Areas"] = [2325.0, 747.0 , 136.0]
# stores the parameters of the efficiency function
# the function is:
# eff(En) = (a0 + a1*x + a2*x^2 + a3*x^3 + a5*x^5 + a7*x^7)/(En)
# with x = Log_10(en) and En = (Gamma Energy in MeV)
# the format is: [a0, a1, a2, a3, a5, a7]
INPUT["HPGe Efficiency Function"] = [8.17090e-03, 1.84907e-03, -3.28729e-04,
                                     -7.60215e-04, 1.87004e-04, -1.16447e-05]
