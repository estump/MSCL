NDSummary.OnToolTipsLoaded("CClass:InertialDataPoint",{1040:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1040\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">InertialDataPoint</div></div></div><div class=\"TTSummary\">Represents a single Inertial Data Point (Extends from DataPoint)</div></div>",1042:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1042\" class=\"NDPrototype NoParameterForm\">InertialDataPoint()</div><div class=\"TTSummary\">Creates an InertialDataPoint object with default, unknown, values</div></div>",1043:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1043\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">InertialDataPoint(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">InertialTypes::</td><td class=\"PType\">ChannelField&nbsp;</td><td class=\"PName last\">field,</td></tr><tr><td class=\"PModifierQualifier first\">InertialTypes::</td><td class=\"PType\">ChannelQualifier&nbsp;</td><td class=\"PName last\">qualifier,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">ValueType&nbsp;</td><td class=\"PName last\">storedAsType,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">anyType&nbsp;</td><td class=\"PName last\">value,</td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">valid</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates an InertialDataPoint object</div></div>",1045:"<div class=\"NDToolTip TVariable LC\"><div class=\"TTSummary\">The InertialTypes::ChannelField of the data point.</div></div>",1046:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1046\" class=\"NDPrototype NoParameterForm\">InertialTypes::ChannelQualifier m_qualifier</div><div class=\"TTSummary\">The InertialTypes::ChannelQualifier of the data point.</div></div>",1047:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1047\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_valid</div><div class=\"TTSummary\">Whether the data point is valid(true) or invalid(false)</div></div>",1049:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1049\" class=\"NDPrototype NoParameterForm\">InertialTypes::ChannelField field() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Channel Field that describes the full MIP &quot;Field&quot; that the data point came in.&nbsp; This is a combination of a MIP &quot;Descriptor ID&quot;, and a MIP &quot;Field ID&quot;.</div></div>",1050:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1050\" class=\"NDPrototype NoParameterForm\">InertialTypes::ChannelQualifier qualifier() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Channel Qualifier that describes the specific channel for the data point.&nbsp; This, combined with the InertialTypes::ChannelField, is a fully unique identifier for the channel.</div></div>",1051:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1051\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> valid() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether the data point is flagged as valid(true) or invalid(false)</div></div>",1052:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1052\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> channelName() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the name of the channel.&nbsp; This is the universal channel name that should be used for uploading to SensorCloud.</div></div>",1053:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1053\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> str() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the string representation of the type of this data point</div></div>",1055:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">Typedef for a vector of InertialDataPoint objects</div></div>"});