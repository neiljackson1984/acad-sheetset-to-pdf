using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmClassWithCustomPropertyBag : AcSmClass
    {

        public AcSmClassWithCustomPropertyBag()
        {
            //
        }

        public AcSmClassWithCustomPropertyBag(XmlElement wEl)
            : base(wEl)
        {
        }

        public AcSmCustomPropertyBag GetCustomPropertyBag() 
        {
            AcSmCustomPropertyBag res = (AcSmCustomPropertyBag)this.FindChild("AcSmCustomPropertyBag");
            if (res == null)
            {
                res = new AcSmCustomPropertyBag();
                this.Child.Add(res);
            }
            return res;
        }

        public AcSmCustomPropertyValue GetCustomProperty(string nName)
        {
            AcSmCustomPropertyBag wCPB = this.GetCustomPropertyBag();
            return wCPB.GetProperty(nName);
        }

        public void SetCustomProperty(string nName, string pValue)
        {
            this.GetCustomProperty(nName).Value = pValue;
        }

        public AcSmProp GetProperty(string nName)
        {
            return (AcSmProp)this.FindChild("AcSmProp", nName);
        }

        public void SetProperty(string nName, string nValue)
        {
            AcSmProp wP = this.GetProperty(nName);
            wP.SetValue(nValue);
        }

    }
}
