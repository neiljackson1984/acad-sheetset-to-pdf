using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmCustomPropertyValue : AcSmClass
    {

        public AcSmCustomPropertyValue(XmlElement wEl)
            : base(wEl)
        {
        }

        protected void SetClass()
        {
            this.ClassName = "AcSmCustomPropertyValue";
            this.clsGuid = Guid.Parse("8D22A2A4-1777-4D78-84CC-69EF741FE954");
            this.fID = Guid.NewGuid();
            this.vt = 13;
        }

        public AcSmCustomPropertyValue(string pName, string pValue)
        {
            this.SetClass();
            this.propname = pName;
            this.Child.Add(new AcSmProp("Flags", 3, "2")); //??
            this.Child.Add(new AcSmProp("Value", 8, pValue));
        }

        public AcSmCustomPropertyValue(int flag, string pName, string pValue)
        {
            this.SetClass();
            this.propname = pName;
            this.Child.Add(new AcSmProp("Flags", 3, flag.ToString())); //??
            this.Child.Add(new AcSmProp("Value", 8, pValue));
        }

        public string Name
        {
            get { return this.propname; }
        }

        protected AcSmProp GetValue()
        {
            return (AcSmProp)this.FindChild("AcSmProp", "Value");
        }

        public string Value
        {
            get
            {
                return this.GetValue().value;
            }
            set
            {
                this.GetValue().value = value;
            }
        }

    }
}
