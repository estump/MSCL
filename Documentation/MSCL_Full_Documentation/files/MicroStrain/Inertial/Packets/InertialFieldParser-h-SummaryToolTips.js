NDSummary.OnToolTipsLoaded("File:MicroStrain/Inertial/Packets/InertialFieldParser.h",{692:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">Typedef for a map of InertialTypes::ChannelField / InertialFieldParser pairs</div></div>",693:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype693\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">InertialFieldParser</div></div></div><div class=\"TTSummary\">Base Class parser for parsing Inertial Data Fields</div></div>",695:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype695\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> parse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">InertialDataField&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">field,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">InertialDataPoints&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">result</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span> = <span class=\"SHNumber\">0</span></td></tr></table></div><div class=\"TTSummary\">Parses an InertialDataField for InertialDataPoints and stores them in the result vector</div></div>",696:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype696\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static void</span> parseField(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">InertialDataField&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">field,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">InertialDataPoints&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">result</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">The static parse function to call that looks through the parser map and parses the field with the correct parser</div></div>",697:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype697\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static</span> ParserMap&amp; getParserMap()</div><div class=\"TTSummary\">Gets the static parser map that contains all the registered parsing classes</div></div>",698:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype698\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static bool</span> registerParser(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">InertialTypes::</td><td class=\"PType\">ChannelField&nbsp;</td><td></td><td class=\"PName last\">field,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">InertialFieldParser&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName last\">parser</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Registers an InertialFieldParser with a InertialTypes::ChannelField.</div></div>",699:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype699\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static bool</span> pointIsValid(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">allFlags,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">flagPos</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks if the flag position for an Inertial Data Point is valid given the full flags value</div></div>"});