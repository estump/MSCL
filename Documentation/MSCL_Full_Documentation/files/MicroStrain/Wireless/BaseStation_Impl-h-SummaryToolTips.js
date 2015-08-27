NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/BaseStation_Impl.h",{3290:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype3290\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">BaseStation_Impl</div></div></div><div class=\"TTSummary\">Contains the implementation for a BaseStation object.</div></div>",3292:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3292\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> BaseStation_Impl(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">Connection&nbsp;</td><td class=\"PName last\">connection,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName last\">baseTimeout</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a BaseStation_Impl object.&nbsp; Note: This will communicate with the BaseStation to get device information, as well as start the data collection thread.</div></div>",3293:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3293\" class=\"NDPrototype NoParameterForm\">~BaseStation_Impl()</div><div class=\"TTSummary\">Destroys the BaseStation object</div></div>",3295:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3295\" class=\"NDPrototype NoParameterForm\">Connection m_connection</div><div class=\"TTSummary\">The Connection object used for communication</div></div>",3296:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3296\" class=\"NDPrototype NoParameterForm\">WirelessPacketCollector m_packetCollector</div><div class=\"TTSummary\">The wireless packet collector used to store wireless data packets</div></div>",3297:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3297\" class=\"NDPrototype NoParameterForm\">std::shared_ptr&lt;ResponseCollector&gt; m_responseCollector</div><div class=\"TTSummary\">The response collector used to find and store wireless command responses</div></div>",3298:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3298\" class=\"NDPrototype NoParameterForm\">std::unique_ptr&lt;WirelessParser&gt; m_parser</div><div class=\"TTSummary\">The wireless parser in charge of parsing all incoming data to this base station</div></div>",3299:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3299\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> m_baseCommandsTimeout</div><div class=\"TTSummary\">The timeout (in milliseconds) to use for base station commands.</div></div>",3300:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3300\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> m_nodeCommandsTimeout</div><div class=\"TTSummary\">The timeout (in milliseconds) to use for node commands.</div></div>",3301:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3301\" class=\"NDPrototype NoParameterForm\">mutable WirelessTypes::Frequency m_frequency</div><div class=\"TTSummary\">The last known radio frequency (WirelessTypes::Frequency) that the BaseStation was known to be on</div></div>",3302:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3302\" class=\"NDPrototype NoParameterForm\">mutable std::unique_ptr&lt;BaseStationEeprom&gt; m_eeprom</div><div class=\"TTSummary\">The BaseStationEeprom that handles reading and writing eeprom values with the BaseStation and eeprom cache.</div></div>",3303:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3303\" class=\"NDPrototype NoParameterForm\">mutable std::unique_ptr&lt;BaseStationEepromHelper&gt; m_eepromHelper</div><div class=\"TTSummary\">The BaseStationEepromHelper used for high level eeprom reads and writes on the BaseStation.</div></div>",3304:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3304\" class=\"NDPrototype NoParameterForm\">mutable std::unique_ptr&lt;BaseStationFeatures&gt; m_features</div><div class=\"TTSummary\">The BaseStationFeatures containing the features for this BaseStation.</div></div>",3305:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3305\" class=\"NDPrototype NoParameterForm\">Timestamp m_lastCommTime</div><div class=\"TTSummary\">A Timestamp representing the last time communication was achieved with the BaseStation.</div></div>",3306:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype3306\" class=\"NDPrototype NoParameterForm\">std::map&lt;NodeAddress, Timestamp&gt; m_nodesLastCommTime</div><div class=\"TTSummary\">A map of NodeAddress to Timestamp objects, holding the last communication time for nodes with this BaseStation.</div></div>",3308:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3308\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static uint32</span> getTimeForBeacon()</div><div class=\"TTSummary\">Gets the system time in UTC seconds since Unix Epoch as close to 0 milliseconds as possible</div></div>",3309:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3309\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> parseData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">DataBuffer&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Callback function that parses any bytes that are in the read buffer to find packets or command responses</div></div>",3310:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3310\" class=\"NDPrototype NoParameterForm\">BaseStationEepromHelper&amp; eeHelper() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets a reference to the BaseStationEepromHelper for this BaseStation.</div></div>",3311:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3311\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual const</span> BaseStationFeatures&amp; features() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets a reference to the BaseStationFeatures for this BaseStation.</div></div>",3312:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3312\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> Timestamp&amp; lastCommunicationTime() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Timestamp for the last time we communicated with the BaseStation.</div></div>",3313:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3313\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> read(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td></td><td class=\"PName last\">eepromAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">result</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Reads the value from the BaseStation for a specified eeprom location.</div></div>",3314:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3314\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> write(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">eepromAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Writes a value to the BaseStation at a specified eeprom location.</div></div>",3315:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3315\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> useEepromCache(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">useCache</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets whether or not to utilize the eeprom cache when configuring this BaseStation (default of enabled). This can be enabled/disabled at any time.&nbsp; Note:	The eeprom cache stores the last known value that was written to / read from the BaseStation for each eeprom location. If this is enabled, any reads will get the last known value from the cache if it exists, and any writes will not write to the BaseStation if the value attempting to be written is the same as that stored in the cache. Caching of these values will still be performed if this is disabled, however, read and write operations will then always reach out to the actual device.</div></div>",3316:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3316\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> clearEepromCache()</div><div class=\"TTSummary\">Clears the eeprom cache for this BaseStation.</div></div>",3317:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3317\" class=\"NDPrototype NoParameterForm\">WirelessTypes::Frequency frequency() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::Frequency representing the radio frequency of this BaseStation.&nbsp; If the frequency is unknown, it will be read from the BaseStation.</div></div>",3318:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3318\" class=\"NDPrototype NoParameterForm\">WirelessTypes::RegionCode regionCode() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::RegionCode representing the region of this BaseStation.</div></div>",3319:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3319\" class=\"NDPrototype NoParameterForm\">Version firmwareVersion() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the firmware version of the BaseStation.</div></div>",3320:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3320\" class=\"NDPrototype NoParameterForm\">WirelessModels::BaseModel model() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the model of the BaseStation.</div></div>",3321:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3321\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> serial() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the serial number of the BaseStation.</div></div>",3322:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3322\" class=\"NDPrototype NoParameterForm\">WirelessTypes::MicroControllerType microcontroller() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the microcontroller of the BaseStation.</div></div>",3323:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3323\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> getNextData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">DataSweep&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName\">sweep,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td></td><td class=\"PName\">timeout&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets the next single DataSweep of sampled data (LDC, Sync Sampling, etc) collected by this BaseStation.</div></div>",3324:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3324\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> getData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">vector&lt;DataSweep&gt;&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName\">sweeps,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td></td><td class=\"PName\">timeout&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span>,</td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td></td><td class=\"PName\">maxSweeps&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets up to the requested amount of DataSweeps of sampled data that was collected by this BaseStation.</div></div>",3325:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3325\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> totalData()</div><div class=\"TTSummary\">Gets the number of DataSweeps that are currently in the data buffer.</div></div>",3326:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3326\" class=\"NDPrototype NoParameterForm\">NodeDiscoveries getNodeDiscoveries()</div><div class=\"TTSummary\">Gets the group of Node Discoveries that were collected by this base station.&nbsp; Calling this function clears out the Node Discovery buffer, so repeatedly calling this will give you any new Node Discoveries.</div></div>",3327:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3327\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> baseCommandsTimeout(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName last\">timeout</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the timeout to use when waiting for responses from base station commands</div></div>",3328:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3328\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> nodeCommandsTimeout(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName last\">timeout</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the timeout to use when waiting for responses from node commands</div></div>",3329:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3329\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> baseCommandsTimeout() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the current timeout to use when waiting for responses from base station commands.</div></div>",3330:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3330\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> nodeCommandsTimeout() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the current timeout to use when waiting for responses from node commands</div></div>",3331:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3331\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual bool</span> ping()</div><div class=\"TTSummary\">Pings the base station</div></div>",3332:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3332\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual uint16</span> readEeprom(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">eepromAddress</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a specific EEPROM address on the BaseStation.&nbsp; If the value stored in the eeprom cache is still valid, this will be returned instead.</div></div>",3333:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3333\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual</span> Value readEeprom(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">EepromLocation&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">location</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a value from the given EepromLocation of the BaseStation.&nbsp; If the value stored in the eeprom cache is still valid, this will be returned instead.</div></div>",3334:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3334\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> writeEeprom(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">eepromAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Writes the specified uint16 value to a specific EEPROM address on the BaseStation.&nbsp; If successful, the cache will be updated with the changed value as well.</div></div>",3335:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3335\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> writeEeprom(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">EepromLocation&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">location,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Value&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">val</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Writes a value to the given EepromLocation of the BaseStation.&nbsp; If successful, the cache will be updated with the changed value as well.</div></div>",3336:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3336\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> Timestamp enableBeacon()</div><div class=\"TTSummary\">Enables the beacon on the base station using the system time (UTC) as its starting timestamp.</div></div>",3337:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3337\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual</span> Timestamp enableBeacon(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">utcTime</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Enables the beacon on the base station using the given UTC timestamp.</div></div>",3338:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3338\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual void</span> disableBeacon()</div><div class=\"TTSummary\">Disables the beacon on the base station.</div></div>",3339:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3339\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> cyclePower()</div><div class=\"TTSummary\">Cycles the power on the base station.</div></div>",3340:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3340\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> resetRadio()</div><div class=\"TTSummary\">Resets the radio on the base station.</div></div>",3341:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3341\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> changeFrequency(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">Frequency&nbsp;</td><td class=\"PName last\">frequency</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Changes the radio frequency of the base station.</div></div>",3342:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3342\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> verifyConfig(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">BaseStationConfig&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">config,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">ConfigIssues&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">outIssues</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Checks whether the settings in the given BaseStationConfig are ok to be written to the BaseStation.&nbsp; Options that are set will also be validated against each other. If an option that needs to be validated isn\'t currently set, it will be read from the BaseStation.</div></div>",3343:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3343\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> applyConfig(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">BaseStationConfig&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">config</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Applies a BaseStationConfig to the Node.</div></div>",3344:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3344\" class=\"NDPrototype NoParameterForm\">WirelessTypes::TransmitPower getTransmitPower() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Reads the WirelessTypes::TransmitPower that is currently set on the BaseStation.</div></div>",3345:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3345\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">BaseStationButton getButtonLongPress(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">buttonNumber</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets the current button settings for a long press action, as a BaseStationButton.</div></div>",3346:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3346\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">BaseStationButton getButtonShortPress(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">buttonNumber</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets the current button settings for a short press action, as a BaseStationButton.</div></div>",3347:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3347\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> getAnalogPairingEnabled() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the current setting for if Analog Pairing is enabled or not.</div></div>",3348:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3348\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> getAnalogTimeoutTime() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Reads the Analog Timeout Time in seconds that is currently set on the BaseStation.</div></div>",3349:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3349\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> getAnalogTimeoutVoltage() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Reads the Analog Timeout Voltage that is currently set on the BaseStation.</div></div>",3350:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3350\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> getAnalogExceedanceEnabled() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Reads the Analog Exceedance enabled/disabled setting that is currently set on the BaseStation.</div></div>",3351:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3351\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">BaseStationAnalogPair getAnalogPair(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">portNumber</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads the BaseStationAnalogPair for the specified port number that is currently set on the BaseStation.</div></div>",3352:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3352\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">const</span> Timestamp&amp; node_lastCommunicationTime(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets the Timestamp for the last time MSCL communicated with the given node address.</div></div>",3353:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3353\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> node_shortPing(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Pings a specific node</div></div>",3354:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3354\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual</span> PingResponse node_ping(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Pings the specified Node.</div></div>",3355:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3355\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> node_sleep(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Puts the Node into a low power, sleep mode.&nbsp; This command attempts to ping the node before sending the sleep command, to verify communication.</div></div>",3356:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3356\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual</span> SetToIdleStatus node_setToIdle(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td></td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">BaseStation&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">base</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Attempts to set the node to idle so that it can be communicated with.</div></div>",3357:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3357\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> node_readEeprom(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td></td><td class=\"PName last\">readVersion,</td></tr><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td></td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td></td><td class=\"PName last\">eepromAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">eepromValue</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Reads a value from EEPROM on the specified Node.</div></div>",3358:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3358\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> node_writeEeprom(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">writeVersion,</td></tr><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">eepromAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Writes a value to EEPROM on the specified Node.</div></div>",3359:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3359\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> node_pageDownload(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td></td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td></td><td class=\"PName last\">pageIndex,</td></tr><tr><td class=\"PType first\">ByteStream&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Download a page of logged data from the Node</div></div>",3360:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3360\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> node_startSyncSampling(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sends the Start Synchronized Sampling command to a Node.</div></div>",3361:"<div class=\"NDToolTip TFunction LC\"><div class=\"TTSummary\">Sends the Start Non-Synchronized Sampling command to a Node.</div></div>",3362:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3362\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> node_armForDatalogging(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td></td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">message</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sends the Arm For Datalogging command to a Node.</div></div>",3363:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3363\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> node_autocal(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td></td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessModels::</td><td class=\"PType\">NodeModel&nbsp;</td><td></td><td class=\"PName last\">model,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Version&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">fwVersion,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">AutoCalResult&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">result</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Performs automatic calibration for a Wireless Node.</div></div>"});